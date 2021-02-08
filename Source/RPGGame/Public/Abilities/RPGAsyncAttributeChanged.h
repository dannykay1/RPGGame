// Copyright Danny Kay 2021.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "AbilitySystemComponent.h"
#include "RPGAsyncAttributeChanged.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, NewValue, float, OldValue);

/**
 * Blueprint node to automatically register a listener for all attribute changes in an AbilitySystemComponent.
 * Useful to use in UI.
 */
UCLASS()
class RPGGAME_API URPGAsyncAttributeChanged : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:
    UPROPERTY(BlueprintAssignable)
    FOnAttributeChanged OnAttributeChanged;

    // Listens for Attribute Changing.
    UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
    static URPGAsyncAttributeChanged* ListenForAttributeChange(class UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);

    // Listens for Attribute Changing.
    // Version that taeks in an array of Attributes.  Check the Attribute output for which Attribute changed.
    static URPGAsyncAttributeChanged* ListenForAttributesChange(class UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes);

	// You must call this function manually when you want the AsyncTask to end.
	// For UMG Widgets, you would call it in the Widget's Destruct event.
    UFUNCTION(BlueprintCallable)
    void EndTask();

protected:
	UPROPERTY()
    UAbilitySystemComponent* ASC;

	FGameplayAttribute AttributeToListenFor;
	TArray<FGameplayAttribute> AttributesToListenFor;

	void AttributeChanged(const FOnAttributeChangeData& Data);
};
