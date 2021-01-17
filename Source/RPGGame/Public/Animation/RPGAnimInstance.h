// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "RPGAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPGGAME_API URPGAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	/* Sets all default values. */
	URPGAnimInstance();

	/* Performs initialization. */
	virtual void NativeInitializeAnimation() override;

	/* Updates the animation. */
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:
	/* The owner of the animation. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Animation")
	class ACharacter* CharacterOwner;

	/* Is character moving? */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsMoving : 1;

	/* Is character falling?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsFalling : 1;

	/* Is character dead?  Based on HealthComponent. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsDead : 1;

	/* Is character crouching?*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	uint8 bIsCrouching : 1;

	/* Pitch of character.  Used for aim offsets. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Pitch;

	/* Speed of the character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Speed;

	/* Direction based on character velocity and rotation. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	float Direction;
};
