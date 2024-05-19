// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "Actors/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

/**
 * 
 */
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:
	AAuraCharacter();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TObjectPtr<UCameraComponent> CameraComponent; //no real reason to choose to make camera in c++ or blueprint, as it doesnt offer any performance benefits. only preference

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent; //no real reason to choose to make camera in c++ or blueprint, as it doesnt offer any performance benefits. only preference
};
