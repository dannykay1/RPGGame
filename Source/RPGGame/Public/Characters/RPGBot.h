// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "Characters/RPGCharacter.h"
#include "RPGBot.generated.h"

/**
 * Base class for all enemies/bots.
 */
UCLASS()
class RPGGAME_API ARPGBot : public ARPGCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARPGBot(const class FObjectInitializer& ObjectInitializer);

protected:
	virtual void BeginPlay() override;

	virtual void Kill() override;

	// Health bar on the bot, will be hidden when bot dies.
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, Category = "Components")
	class UWidgetComponent* HealthBarComponent;
};
