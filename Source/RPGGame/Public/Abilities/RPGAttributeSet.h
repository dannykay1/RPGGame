// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"

// Uses macros from AttributeSet.h
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


UCLASS()
class URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	URPGAttributeSet();

	// AttributeSet Overrides
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Health")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth)

	// Damage is a meta attribute used by the DamageExecution to calculate final damage, which then turns into -Health
	UPROPERTY(BlueprintReadOnly, Category = "Damage", meta = (HideFromLevelInfos))
	FGameplayAttributeData Damage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Damage)

	UPROPERTY(BlueprintReadOnly, Category = "Shield")
	FGameplayAttributeData Shield;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Shield)

	UPROPERTY(BlueprintReadOnly, Category = "Shield")
	FGameplayAttributeData MaxShield;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxShield)

	UPROPERTY(BlueprintReadOnly, Category = "Character Level")
	FGameplayAttributeData CharacterLevel;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CharacterLevel)

	// Experience points gained from killing enemies.
	UPROPERTY(BlueprintReadOnly, Category = "XP")
	FGameplayAttributeData XP;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, XP)

	// Experience points awarded to the character's killers. Used to level up
	UPROPERTY(BlueprintReadOnly, Category = "XP")
	FGameplayAttributeData XPBounty;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, XPBounty)

protected:
	// Helper function to proportionally adjust the value of an attribute when it's associated max attribute changes.
	// (i.e. When MaxHealth increases, Health increases by an amount that maintains the same percentage as before)
	void AdjustAttributeForMaxChange(FGameplayAttributeData& AffectedAttribute, const FGameplayAttributeData& MaxAttribute, float NewMaxValue, const FGameplayAttribute& AffectedAttributeProperty);
};
