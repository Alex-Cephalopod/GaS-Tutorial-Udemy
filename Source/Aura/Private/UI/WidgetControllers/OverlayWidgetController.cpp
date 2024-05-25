// Copyright Cephalo-Alex


#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AttribSet = CastChecked<UAuraAttributeSet>(AttributeSet);
	if (AttribSet)
	{
		OnHealthChanged.Broadcast(AttribSet->GetHealth());
		OnMaxHealthChanged.Broadcast(AttribSet->GetMaxHealth());
	}
	
}
