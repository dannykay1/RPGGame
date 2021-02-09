// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "RPGAttributeProgressBar.generated.h"

/**
 * This will be a progress bar that will update any attribute (value / max value).
 */
UCLASS()
class RPGGAME_API URPGAttributeProgressBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void InitializeProgressBar(class UAbilitySystemComponent* ASC, FGameplayAttribute Current, FGameplayAttribute Max);
};
