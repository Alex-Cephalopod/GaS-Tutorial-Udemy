// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraBaseGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"
/**
 * 
 */
class AAuraProjectile;
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraBaseGameplayAbility
{
	GENERATED_BODY()
	
public:

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
		const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<AAuraProjectile> ProjectileClass; 

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation);

private:

};
