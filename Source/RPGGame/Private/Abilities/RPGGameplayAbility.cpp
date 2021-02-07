// Copyright Danny Kay 2021.

#include "Abilities/RPGGameplayAbility.h"

URPGGameplayAbility::URPGGameplayAbility()
{
}

void URPGGameplayAbility::OnAvatarSet(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec)
{
	Super::OnAvatarSet(ActorInfo, Spec);
}
