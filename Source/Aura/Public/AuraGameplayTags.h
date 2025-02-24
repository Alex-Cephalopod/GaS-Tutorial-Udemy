// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

/**
 *  Aura Gameplay Tags
 * 
 *  Single containing native gameplay tags (made and available in C++).
 */

struct FAuraGameplayTags
{
public:

	static const FAuraGameplayTags& Get() { return GameplayTags; };

	static void InitializeNativeGameplayTags();

#pragma region GameplayTags

	/* Primary Attributes */
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Vigor;

	/* Secondary Attributes */
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_BlockChance;
	FGameplayTag Attributes_Secondary_CritHitChance;
	FGameplayTag Attributes_Secondary_CritHitDamage;
	FGameplayTag Attributes_Secondary_CritHitResistance;
	FGameplayTag Attributes_Secondary_HealthRegen;
	FGameplayTag Attributes_Secondary_ManaRegen;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

	/* Vital Attributes */

	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;

	/* Input Tags */

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

	/* Damage Tags */

	FGameplayTag Damage;

	/* Effects Tags */

	FGameplayTag Effects_HitReact;

#pragma endregion

protected:
	
private:

	static FAuraGameplayTags GameplayTags;

};
