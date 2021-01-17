// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayTagContainer.h"
#include "RPGCharacterMovementComponent.generated.h"

/**
 *
 */
UCLASS()
class RPGGAME_API URPGCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	URPGCharacterMovementComponent();

	virtual float GetMaxSpeed() const override;

protected:
	FGameplayTag SprintTag;
	FGameplayTag ADSTag;
};
