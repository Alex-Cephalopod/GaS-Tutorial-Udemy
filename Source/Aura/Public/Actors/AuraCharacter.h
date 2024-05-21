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

	//Q: Is there a PossessedBy function?
	//A: Yes, it is inherited from AActor. It is called PossessedBy().
	//Q: is it public?
	//A: Yes, it is public.

	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		TObjectPtr<UCameraComponent> CameraComponent; //no real reason to choose to make camera in c++ or blueprint, as it doesnt offer any performance benefits. only preference

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent; //no real reason to choose to make camera in c++ or blueprint, as it doesnt offer any performance benefits. only preference

private:

	void SetAbilityActorInfo();
};
