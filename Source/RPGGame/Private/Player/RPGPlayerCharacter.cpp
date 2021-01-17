// Copyright Danny Kay 2021.

#include "Player/RPGPlayerCharacter.h"
#include "RPGGame/RPGGame.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ARPGPlayerCharacter::ARPGPlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = true;
	SpringArmComponent->SetRelativeLocation(FVector(0.f, 30.f, 80.f));

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->NavAgentProps.bCanCrouch = true;
	bUseControllerRotationYaw = true;
}

void ARPGPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->BindAbilityActivationToInputComponent(InputComponent, FGameplayAbilityInputBinds(FString("ConfirmTarget"),
			FString("CancelTarget"), FString("ERPGAbilityInputID"), static_cast<int32>(ERPGAbilityInputID::Confirm), static_cast<int32>(ERPGAbilityInputID::Cancel)));
	}
}

FVector ARPGPlayerCharacter::GetPawnViewLocation() const
{
	if (CameraComponent && SpringArmComponent)
	{
		FVector ViewLocation = CameraComponent->GetComponentLocation();

		// Offset the view location by arm length so character cannot hit actors behind this character.
		ViewLocation += CameraComponent->GetForwardVector() * SpringArmComponent->TargetArmLength;

		return ViewLocation;
	}

	return Super::GetPawnViewLocation();
}