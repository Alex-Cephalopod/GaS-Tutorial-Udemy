// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AuraBaseGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraBaseGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	FGameplayTag StartupInputTag;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Damage")
	FScalableFloat Damage;
};
