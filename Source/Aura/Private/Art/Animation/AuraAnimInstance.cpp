// Copyright Cephalo-Alex


#include "Art/Animation/AuraAnimInstance.h"
#include "Actors/AuraCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

UAuraAnimInstance::UAuraAnimInstance()
{
}

void UAuraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	//AuraCharacter = Cast<AAuraCharacter>(TryGetPawnOwner());
	if (AuraCharacter = Cast<AAuraCharacter>(TryGetPawnOwner()))
	{
		CharacterMovementComponent = AuraCharacter->GetCharacterMovement();
	}
}

void UAuraAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (AuraCharacter)
	{
		GroundSpeed = CharacterMovementComponent->Velocity.Length();
	}
}
