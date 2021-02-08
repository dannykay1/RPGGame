// Copyright Danny Kay 2021.

#include "Abilities/RPGAsyncAttributeChanged.h"


URPGAsyncAttributeChanged* URPGAsyncAttributeChanged::ListenForAttributeChange(class UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	URPGAsyncAttributeChanged* WaitForAttributeChangedTask = NewObject<URPGAsyncAttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributeToListenFor = Attribute;

	if (!IsValid(AbilitySystemComponent) || !Attribute.IsValid())
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &URPGAsyncAttributeChanged::AttributeChanged);

	return WaitForAttributeChangedTask;
}


URPGAsyncAttributeChanged* URPGAsyncAttributeChanged::ListenForAttributesChange(class UAbilitySystemComponent* AbilitySystemComponent, TArray<FGameplayAttribute> Attributes)
{
	URPGAsyncAttributeChanged* WaitForAttributeChangedTask = NewObject<URPGAsyncAttributeChanged>();
	WaitForAttributeChangedTask->ASC = AbilitySystemComponent;
	WaitForAttributeChangedTask->AttributesToListenFor = Attributes;

	if (!IsValid(AbilitySystemComponent) || Attributes.Num() < 1)
	{
		WaitForAttributeChangedTask->RemoveFromRoot();
		return nullptr;
	}

	for (FGameplayAttribute Attribute : Attributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute).AddUObject(WaitForAttributeChangedTask, &URPGAsyncAttributeChanged::AttributeChanged);
	}

	return WaitForAttributeChangedTask;
}


void URPGAsyncAttributeChanged::EndTask()
{
	if (IsValid(ASC))
	{
		ASC->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);

		for (FGameplayAttribute Attribute : AttributesToListenFor)
		{
			ASC->GetGameplayAttributeValueChangeDelegate(Attribute).RemoveAll(this);
		}
	}

	SetReadyToDestroy();
	MarkPendingKill();
}


void URPGAsyncAttributeChanged::AttributeChanged(const FOnAttributeChangeData& Data)
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.NewValue, Data.OldValue);
}
