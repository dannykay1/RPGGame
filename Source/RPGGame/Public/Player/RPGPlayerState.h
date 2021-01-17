// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RPGPlayerState.generated.h"


UCLASS()
class RPGGAME_API ARPGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ARPGPlayerState();

	// Implement IAbilitySystemInterface
	class UAbilitySystemComponent* GetAbilitySystemComponent() const override
	{
		return AbilitySystemComponent;
	}

	class URPGAttributeSet* GetAttributeSetComponent() const
	{
		return AttributeSetComponent;
	}

protected:
	UPROPERTY()
	class UAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY()
	class URPGAttributeSet* AttributeSetComponent;
};
