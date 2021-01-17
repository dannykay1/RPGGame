// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "RPGGame/RPGGame.h"
#include "RPGGameplayAbility.generated.h"

UCLASS()
class RPGGAME_API URPGGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

public:
	URPGGameplayAbility();

	// Abilities with this set will automatically activate when the input is pressed
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Ability")
	ERPGAbilityInputID AbilityInputID = ERPGAbilityInputID::None;
};
