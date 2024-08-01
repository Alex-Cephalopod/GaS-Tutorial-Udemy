// Copyright Cephalo-Alex


#include "UI/WidgetControllers/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);

	/*naive approach*/
	/*FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FAuraGameplayTags::Get().Attributes_Primary_Strength);
	Info.AttributeValue = AS->GetStrength();
	AttributeInfoDelegate.Broadcast(Info);*/

	/*optimized approach*/
	
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	//this code snippet will broadcast any changes with our primary and secondary values
	UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	check(AttributeInfo);
	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this, Pair, AS](const FOnAttributeChangeData& ChangeData)
			{ 
				BroadcastAttributeInfo(Pair.Key, Pair.Value());
			} 
		); 
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag); //Pair.Key
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);//Pair.Value().GetNumericValue(AS);  
	AttributeInfoDelegate.Broadcast(Info);  
}

/*NOTES

1. Pair.Value.Excecute().GetNumericValue(AS); //excecutes function bound to this delegate (check UAuraAttributeSet for something like StrengthDelegate.BindStatic(GetStrengthAttribute); It excecutes that)
	This line is now defunct, and replaced with Pair.Value().GetNumericalValue(AS); (Check AuraAttributeSet.h)

2. FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS); //excecutes function bound to this delegate (check UAuraAttributeSet for something like StrengthDelegate.BindStatic(GetStrengthAttribute); It excecutes that)
		AttributeInfoDelegate.Broadcast(Info);
*/