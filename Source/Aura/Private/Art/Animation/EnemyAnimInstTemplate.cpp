// Copyright Cephalo-Alex


#include "Art/Animation/EnemyAnimInstTemplate.h"
#include "Actors/AuraEnemy.h"
#include "GameFramework/CharacterMovementComponent.h"

void UEnemyAnimInstTemplate::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	TObjectPtr<AAuraEnemy> AuraEnemy = Cast<AAuraEnemy>(TryGetPawnOwner());
	if (AuraEnemy)
	{
		MovementComponent = AuraEnemy->GetCharacterMovement();
	}
}

void UEnemyAnimInstTemplate::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (MovementComponent)
	{
		GroundSpeed = MovementComponent->Velocity.Length();
	}
}
