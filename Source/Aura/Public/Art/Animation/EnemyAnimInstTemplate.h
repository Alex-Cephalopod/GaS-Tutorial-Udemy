// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "EnemyAnimInstTemplate.generated.h"

/**
 * 
 */
class UCharacterMovementComponent;

UCLASS()
class AURA_API UEnemyAnimInstTemplate : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Animation")
		float GroundSpeed;

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly, Category = "Enemy Animation")
		TObjectPtr<UCharacterMovementComponent> MovementComponent;
	
};
