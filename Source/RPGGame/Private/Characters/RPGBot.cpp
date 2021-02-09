// Copyright Danny Kay 2021.

#include "Characters/RPGBot.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Characters/RPGCharacterMovementComponent.h"
#include "AIController.h"
#include "BrainComponent.h"
#include "UI/RPGAttributeProgressBar.h"
#include "Abilities/RPGAttributeSet.h"


ARPGBot::ARPGBot(const class FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<URPGCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	HealthBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("HealthBar"));
	HealthBarComponent->SetupAttachment(GetRootComponent());
	HealthBarComponent->SetRelativeLocation(FVector(0.f, 0.f, 45.f));
	HealthBarComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarComponent->SetDrawSize(FVector2D(125.f, 5.f));

	HealthBarComponent->SetWidgetClass(URPGAttributeProgressBar::StaticClass());
}


void ARPGBot::BeginPlay()
{
	Super::BeginPlay();

	URPGAttributeProgressBar* ProgressBar = Cast<URPGAttributeProgressBar>(HealthBarComponent->GetUserWidgetObject());
	if (ProgressBar)
	{
		ProgressBar->InitializeProgressBar(GetAbilitySystemComponent(), AttributeSetComponent->GetHealthAttribute(), AttributeSetComponent->GetMaxHealthAttribute());
		UE_LOG(LogTemp, Warning, TEXT("IS progress Bar!"));
	}
}


void ARPGBot::Kill()
{
	Super::Kill();

	if (HealthBarComponent)
	{
		HealthBarComponent->SetVisibility(false);
	}

	GetCharacterMovement()->StopMovementImmediately();

	AAIController* AIController = Cast<AAIController>(GetController());
	if (AIController)
	{
		if (AIController->BrainComponent)
		{
			AIController->BrainComponent->StopLogic("Dead");
		}
	}

	GetCapsuleComponent()->SetCollisionProfileName("Ragdoll");
	GetMesh()->SetCollisionProfileName("Ragdoll");

	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
	GetMesh()->SetCollisionResponseToChannel(ECC_GameTraceChannel1, ECR_Ignore);
}
