// Copyright Danny Kay 2021.

#include "Animation/RPGAnimInstance.h"
#include "Characters/RPGCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AbilitySystemComponent.h"

URPGAnimInstance::URPGAnimInstance()
{
	bIsMoving = false;
	bIsFalling = false;
	Speed = 0.0f;
	Direction = 0.0f;
}

void URPGAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	APawn* PawnOwner = TryGetPawnOwner();
	if (PawnOwner)
	{
		CharacterOwner = Cast<ARPGCharacter>(PawnOwner);
	}
}

void URPGAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!CharacterOwner)
	{
		return;
	}

	FVector Velocity = CharacterOwner->GetVelocity();

	// Zero out z velocity so animation only uses x and y values for speed.
	Velocity.Z = 0.0f;

	Speed = Velocity.Size();

	bIsMoving = Speed > 0.1f;

	bIsDead = !CharacterOwner->IsAlive();

	if (CharacterOwner->GetCharacterMovement())
	{
		bIsFalling = CharacterOwner->GetCharacterMovement()->IsFalling();
		bIsCrouching = CharacterOwner->GetCharacterMovement()->IsCrouching();
	}

	Direction = CalculateDirection(Velocity, CharacterOwner->GetActorRotation());

	FRotator ControlRotation = CharacterOwner->GetControlRotation();
	FRotator ActorRotation = CharacterOwner->GetActorRotation();

	FRotator CurrentRotation = FRotator(Pitch, 0.0f, 0.0f);
	FRotator TargetRotation = UKismetMathLibrary::ComposeRotators(ControlRotation, ActorRotation);

	FRotator FinalRotator = UKismetMathLibrary::RInterpTo(CurrentRotation, TargetRotation, DeltaSeconds, 15.0f);
	Pitch = UKismetMathLibrary::ClampAngle(FinalRotator.Pitch, -90.0f, 90.0f);
}