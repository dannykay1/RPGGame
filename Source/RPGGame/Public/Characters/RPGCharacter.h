// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "RPGCharacter.generated.h"

UCLASS()
class ARPGCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGCharacter(const class FObjectInitializer& ObjectInitializer);

	// Used to initialize ability system component.
	virtual void PossessedBy(AController* NewController) override;

	// Implement IAbilitySystemInterface
	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	class URPGAttributeSet* GetAttributeSetComponent() const
	{
		return AttributeSetComponent;
	}

	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GiveAbility(TSubclassOf<URPGGameplayAbility> AbilityToGive);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	class URPGAttributeSet* AttributeSetComponent;
	
	// Default abilities for this Character. These will be removed on Character death and regiven if Character respawns.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class URPGGameplayAbility>> CharacterAbilities;

	// Default attributes for a character for initializing on spawn/respawn.
	// This is an instant GE that overrides the values for attributes that get reset on spawn/respawn.
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TSubclassOf<class UGameplayEffect> DefaultAttributes;

	// These effects are only applied one time on startup
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<class UGameplayEffect>> StartupEffects;

	// Grant abilities on the Server. The Ability Specs will be replicated to the owning client.
	virtual void AddCharacterAbilities();

	// Initialize the Character's attributes. These will be set on spawn/respawn.
	virtual void InitializeAttributes();

	// Initialize with any effects such as heal over time, respawn invincibility, etc.
	virtual void AddStartupEffects();

	FDelegateHandle HealthChangedDelegateHandle;

	// Attribute changed callbacks
	virtual void HealthChanged(const FOnAttributeChangeData& Data);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void OnHealthChanged(float CurrentValue, float MaxValue);
};
