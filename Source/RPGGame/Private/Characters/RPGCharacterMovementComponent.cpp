// Copyright Danny Kay 2021.

#include "Characters/RPGCharacterMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"
#include "Characters/RPGCharacter.h"
#include "Abilities/RPGAttributeSet.h"


URPGCharacterMovementComponent::URPGCharacterMovementComponent()
{
	SprintTag = FGameplayTag::RequestGameplayTag(FName("Ability.Movement.Sprint"));
	ADSTag = FGameplayTag::RequestGameplayTag(FName("Ability.Movement.ADS"));
}

float URPGCharacterMovementComponent::GetMaxSpeed() const
{
	ARPGCharacter* Owner = Cast<ARPGCharacter>(GetOwner());
	if (!Owner || !Owner->GetAttributeSetComponent() || !Owner->GetAttributeSetComponent())
	{
		return Super::GetMaxSpeed();
	}
	
	if (Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(ADSTag))
	{
		return MaxWalkSpeedCrouched;
	}
	else if (Owner->GetAbilitySystemComponent()->HasMatchingGameplayTag(SprintTag))
	{
		return 1000.f;
	}

	return Super::GetMaxSpeed();
}
