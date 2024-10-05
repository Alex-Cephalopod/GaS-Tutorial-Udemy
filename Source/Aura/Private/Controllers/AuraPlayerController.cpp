// Copyright Cephalo-Alex


#include "Controllers/AuraPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Interfaces/EnemyInterface.h"
#include "Input/AuraInputComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Components/SplineComponent.h"
#include "AuraGameplayTags.h"
#include "NavigationSystem.h"
#include "NavigationPath.h"
#include "GameFramework/Character.h"
#include "UI/Widgets/DamageTextComponent.h"

AAuraPlayerController::AAuraPlayerController()
{
	//NOTE: if single player, we can set this to false to save bandwidth.
	bReplicates = true; // This is a multiplayer game. We need to replicate this controller.

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AAuraPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();

	AutoRun();
}

void AAuraPlayerController::ShowDamageNumber_Implementation(float DamageAmount, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass) //target character could have a pending kill call, so IsValid is used
	{
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextComponentClass);
		DamageText->RegisterComponent(); //manually register the component to the world
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageText->SetDamageText(DamageAmount);
	}
}

void AAuraPlayerController::AutoRun()
{
	if (!bAutoRunning) return;

	if (APawn* ControlledPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControlledPawn->GetActorLocation(), ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline, ESplineCoordinateSpace::World);
		ControlledPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();

		if (DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
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

	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(AuraMoveAction, ETriggerEvent::Triggered, this, &AAuraPlayerController::Move);
	AuraInputComponent->BindAction(AuraShiftAction, ETriggerEvent::Started, this, &AAuraPlayerController::ShiftPressed);
	AuraInputComponent->BindAction(AuraShiftAction, ETriggerEvent::Completed, this, &AAuraPlayerController::ShiftReleased);

	AuraInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, 
		&ThisClass::AbilityInputTagReleased, &ThisClass::AbilityInputTagHeld);
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
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	if (!CursorHit.bBlockingHit) return;

	LastEnemy = CurrentEnemy;
	CurrentEnemy = CursorHit.GetActor();


	if (LastEnemy != CurrentEnemy)
	{
		if (LastEnemy) LastEnemy->UnhighlightActor();
		if (CurrentEnemy) CurrentEnemy->HighlightActor();
	}
}

void AAuraPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 3.f, FColor::Red, *InputTag.ToString());
	if (InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = CurrentEnemy ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(2, 5.f, FColor::Blue, *InputTag.ToString());
	/*if (!GetASC()) return;
	GetASC()->AbilityInputTagReleased(InputTag);*/

	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB)) 
	{
		if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);
		return;
		
	}

	if (GetASC()) GetASC()->AbilityInputTagReleased(InputTag);

	if (!bTargeting && !bShiftKeyDown)
	{
		const APawn* ControlledPawn = GetPawn();

		if (FollowTime <= ShortPressThreshold && ControlledPawn)
		{
			if (UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(this, ControlledPawn->GetActorLocation(), CachedDestination))
			{
				Spline->ClearSplinePoints();

				for (const FVector& PointLocation : NavPath->PathPoints)
				{
					Spline->AddSplinePoint(PointLocation, ESplineCoordinateSpace::World);
				}
				CachedDestination = NavPath->PathPoints.Last();
				bAutoRunning = true;
			}

		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if (GetASC()) GetASC()->AbilityInputTagHeld(InputTag);
		return;
	}

	if (bTargeting || bShiftKeyDown)
	{
		if (GetASC())GetASC()->AbilityInputTagHeld(InputTag);
	}
	else
	{
		//click to move behavior
		FollowTime += GetWorld()->GetDeltaSeconds(); 

		if (CursorHit.bBlockingHit) CachedDestination = CursorHit.ImpactPoint;

		if (APawn* ControlledPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControlledPawn->GetActorLocation()).GetSafeNormal();
			ControlledPawn->AddMovementInput(WorldDirection); //hold mouse button to move if not targeting anything
		}

		/*FVector MouseLocation = CursorHit.ImpactPoint;
		GEngine->AddOnScreenDebugMessage(3, 5.f, FColor::Green, MouseLocation.ToString());*/
	}

}

UAuraAbilitySystemComponent* AAuraPlayerController::GetASC()
{
	if (!AuraAbilitySystemComponent)
	{
		UAbilitySystemComponent* Component = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<AActor>());
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(Component);
	}
	return AuraAbilitySystemComponent;
}


/* NOTES


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




*/