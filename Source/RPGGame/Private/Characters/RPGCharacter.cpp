// Copyright Danny Kay 2021.

#include "Characters/RPGCharacter.h"
#include "AbilitySystemComponent.h"
#include "Abilities/RPGAttributeSet.h"
#include "Abilities/GameplayAbility.h"
#include "Abilities/RPGGameplayAbility.h"
#include "GameplayAbilitySpec.h"

// Sets default values
ARPGCharacter::ARPGCharacter(const class FObjectInitializer& ObjectInitializer)
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AttributeSetComponent = CreateDefaultSubobject<URPGAttributeSet>(TEXT("AttributeSetComponent"));
}

void ARPGCharacter::BeginPlay()
{
	Super::BeginPlay();

	AddCharacterAbilities();
	InitializeAttributes();
	AddStartupEffects();
}

void ARPGCharacter::AddCharacterAbilities()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	for (TSubclassOf<URPGGameplayAbility>& StartupAbility : CharacterAbilities)
	{
		AbilitySystemComponent->GiveAbility(
			FGameplayAbilitySpec(StartupAbility,
			1,
			static_cast<int32>(StartupAbility.GetDefaultObject()->AbilityInputID),
			this));
	}
}

void ARPGCharacter::InitializeAttributes()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributes, 1, EffectContext);
	if (NewHandle.IsValid())
	{
		FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
	}
}

void ARPGCharacter::AddStartupEffects()
{
	if (!AbilitySystemComponent)
	{
		return;
	}

	FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
	EffectContext.AddSourceObject(this);

	for (TSubclassOf<UGameplayEffect> GameplayEffect : StartupEffects)
	{
		FGameplayEffectSpecHandle NewHandle = AbilitySystemComponent->MakeOutgoingSpec(GameplayEffect, 1, EffectContext);
		if (NewHandle.IsValid())
		{
			FActiveGameplayEffectHandle ActiveGEHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*NewHandle.Data.Get(), AbilitySystemComponent);
		}
	}
}