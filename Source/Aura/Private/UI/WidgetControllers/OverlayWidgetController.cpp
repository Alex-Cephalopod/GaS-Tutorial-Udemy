// Copyright Cephalo-Alex


#include "UI/WidgetControllers/OverlayWidgetController.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "GAmeplayEffectTypes.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	UAuraAttributeSet* AttribSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	OnHealthChanged.Broadcast(AttribSet->GetHealth());
	OnMaxHealthChanged.Broadcast(AttribSet->GetMaxHealth());
	OnManaChanged.Broadcast(AttribSet->GetMana());
	OnMaxManaChanged.Broadcast(AttribSet->GetMaxMana());
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	UAuraAttributeSet* AttribSet = CastChecked<UAuraAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttribSet->GetHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnHealthChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttribSet->GetMaxHealthAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttribSet->GetManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnManaChanged.Broadcast(Data.NewValue); 
			}
	);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
		AttribSet->GetMaxManaAttribute()).AddLambda(
			[this](const FOnAttributeChangeData& Data) {
				OnMaxManaChanged.Broadcast(Data.NewValue); 
			}
	);


	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& AssetTags)->void
		{
			for (const FGameplayTag& Tag : AssetTags) //const FGameplayTag& Tag is done to avoid making a copy of the tag
			{
				//"A.1".MatchesTag("A") will return True, "A".MatchesTag("A.1") will return False
				//for example, say that tag is "Message.HealthPotion"
				//"Message.HealthPotion".MatchesTag("Message") will return True, "Message".MatchesTag("Message.HealthPotion") will return False
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if (Tag.MatchesTag(MessageTag))
				{
					//TO DO: Broadcast the tag to the Widget Controller
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);
}

//The below was changed from linking a function to the delegate to linking a lambda function to the delegate
//AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(
//	AttribSet->GetHealthAttribute()).AddUObject(this, &UOverlayWidgetController::HealthChanged);

//function removed (and any similar function (cough cough max health max mana and mana))
/* void UOverlayWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
} */