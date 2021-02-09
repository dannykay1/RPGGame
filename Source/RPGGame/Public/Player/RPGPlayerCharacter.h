// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RPGCharacter.h"
#include "RPGPlayerCharacter.generated.h"

/**
 * Base class for an player/hero characters.
 */
UCLASS()
class RPGGAME_API ARPGPlayerCharacter : public ARPGCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGPlayerCharacter(const class FObjectInitializer& ObjectInitializer);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual FVector GetPawnViewLocation() const override;

protected:
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArmComponent;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UCameraComponent* CameraComponent;
};
