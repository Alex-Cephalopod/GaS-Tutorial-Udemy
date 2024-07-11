// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "Actors/AuraCharacterBase.h"
#include "Interfaces/EnemyInterface.h"
#include "AuraEnemy.generated.h"

/**
 * 
 */

UCLASS()
class AURA_API AAuraEnemy : public AAuraCharacterBase, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAuraEnemy();

	virtual void HighlightActor() override;
	virtual void UnhighlightActor() override;

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadOnly)
		bool bHighlighted = false;


	/** COMBAT INTERFACE */

	virtual int32 GetPlayerLevel() override;

	/** END COMBAT INTERFACE **/

protected:

	virtual void BeginPlay() override;

	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Default Class")
	int32 Level = 1;
private:
	
};
