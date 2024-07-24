// Copyright Cephalo-Alex


#include "UI/WidgetControllers/AttributeMenuWidgetController.h"

#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "AuraGameplayTags.h"

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
		FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
		Info.AttributeValue = Pair.Value().GetNumericValue(AS); //excecutes function bound to this delegate (check UAuraAttributeSet for something like StrengthDelegate.BindStatic(GetStrengthAttribute); It excecutes that)
		AttributeInfoDelegate.Broadcast(Info);
	}
}

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	
}

/*NOTES

1. Pair.Value.Excecute().GetNumericValue(AS); //excecutes function bound to this delegate (check UAuraAttributeSet for something like StrengthDelegate.BindStatic(GetStrengthAttribute); It excecutes that)
	This line is now defunct, and replaced with Pair.Value().GetNumericalValue(AS); (Check AuraAttributeSet.h)
*/