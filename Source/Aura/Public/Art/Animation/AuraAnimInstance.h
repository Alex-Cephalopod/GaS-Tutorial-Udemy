// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AuraAnimInstance.generated.h"

/**
 * 
 */
class UCharacterMovementComponent;
class AAuraCharacter;

UCLASS()
class AURA_API UAuraAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UAuraAnimInstance();

	UPROPERTY(BlueprintReadOnly, Category = "Aura Animation")
		float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = "Aura Animation")
		bool bShouldMove;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aura Animation")
		float MovementThreshold = 3.0f;

protected:
	virtual void NativeInitializeAnimation() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	//A: That's fine, but it's better to store the component in a variable. It's more efficient
	UPROPERTY(BlueprintReadOnly, Category = "Aura Animation")
		TObjectPtr<UCharacterMovementComponent> CharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Aura Animation")
		TObjectPtr<AAuraCharacter> AuraCharacter;
};
