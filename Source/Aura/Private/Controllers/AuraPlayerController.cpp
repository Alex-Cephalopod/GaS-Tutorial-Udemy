// Copyright Cephalo-Alex


#include "Controllers/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Interfaces/EnemyInterface.h"

AAuraPlayerController::AAuraPlayerController()
{
	bReplicates = true; // This is a multiplayer game. We need to replicate this controller.

	//NOTE: if single player, we can set this to false to save bandwidth.
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}



void AAuraPlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* LocalPlayerE = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (LocalPlayerE)
	{
		LocalPlayerE->AddMappingContext(AuraContext, 0);
	}

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	// Set the input mode to game and UI
	// can be used for menus, in game conversations, UI, etc.
	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void AAuraPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInput = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInput->BindAction(AuraMoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
}

void AAuraPlayerController::Move(const FInputActionValue& Value)
{
	const FVector2D MoveDirection = Value.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, MoveDirection.Y);
		ControlledPawn->AddMovementInput(RightDirection, MoveDirection.X);
	}
}

void AAuraPlayerController::CursorTrace()
{
	FHitResult cursorHit;

	GetHitResultUnderCursor(ECC_Visibility, false, cursorHit);

	if (!cursorHit.bBlockingHit)
		return;

	LastEnemy = CurrentEnemy;
	CurrentEnemy = cursorHit.GetActor();

	/** 
	* Line trace from cursor scenarios:
	*	A. LastEnemy is nullptr, CurrentEnemy is nullptr
	*		- do nothing
	* 
	*	B. LastEnemy is nullptr, CurrentEnemy is valid
	*		- call HighlightActor on CurrentEnemy
	* 
	*	C. LastEnemy is valid, CurrentEnemy is nullptr
	*		- call UnhighlightActor on LastEnemy
	* 
	*	D. LastEnemy is valid, CurrentEnemy is valid, LastEnemy != CurrentEnemy
	*		- call UnhighlightActor on LastEnemy
	*		- call HighlightActor on CurrentEnemy
	* 
	*	E. LastEnemy is valid, CurrentEnemy is valid, LastEnemy == CurrentEnemy
	*		- do nothing
	*/

	if (!LastEnemy)
	{
		if (CurrentEnemy)
		{
			//Case B
			CurrentEnemy->HighlightActor();
		}
		else
		{
			//Case A
		}
	}
	else // LastEnemy is valid
	{
		if (!CurrentEnemy)
		{
			//Case C
			LastEnemy->UnhighlightActor();
		}
		else // CurrentEnemy is valid
		{
			if (LastEnemy != CurrentEnemy)
			{
				//Case D
				LastEnemy->UnhighlightActor();
				CurrentEnemy->HighlightActor();
			}
			else
			{
				//Case E
			}
		}
	}
}
