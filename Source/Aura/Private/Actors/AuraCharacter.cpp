// Copyright Cephalo-Alex


#include "Actors/AuraCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "States/AuraPlayerState.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "UI/HUD/AuraHUD.h"
#include "Controllers/AuraPlayerController.h"

AAuraCharacter::AAuraCharacter()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));

	SpringArmComponent->SetupAttachment(RootComponent);
	CameraComponent->SetupAttachment(SpringArmComponent);

	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 400.0f, 0.0f); // Default Rotation Rate
	GetCharacterMovement()->bConstrainToPlane = true; // Constrain movement to the XZ plane //typical for top down games
	GetCharacterMovement()->bSnapToPlaneAtStart = true; // Snap to the XZ plane at start //typical for top down games

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	//Q: is there a Get Player State function?
	//A: Yes, it is inherited from AActor. It is called GetPlayerState().
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	//Init ability Actor info for Server

	InitAbilityActorInfo();
	
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	//Init ability Actor info for Client
	InitAbilityActorInfo();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	//For characters using a Player State, one needs to set these on a PossessedBy event and a OnRep_PlayerState event.
	
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>(); 
	check(AuraPlayerState); 
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState, this); 
	Cast<UAuraAbilitySystemComponent>(AuraPlayerState->GetAbilitySystemComponent())->AbilityActorInfoSet();
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent(); 
	AttributeSet = AuraPlayerState->GetAttributeSet(); 

	//Try and call the InitOverlay function from the HUD
	if (AAuraPlayerController* AuraPlayerController = Cast<AAuraPlayerController>(GetController())) { //CastChecked throws an error on the second player (client)

		if (AAuraHUD* HUD = CastChecked<AAuraHUD>(GetWorld()->GetFirstPlayerController()->GetHUD())) 
		{
			HUD->InitOverlay(AuraPlayerController, AuraPlayerState, AbilitySystemComponent, AttributeSet); 
		}
	}

	//If not susing player state, init using:
	// PossessedBy for Server
	// AcknowledgePossession for Client
}
