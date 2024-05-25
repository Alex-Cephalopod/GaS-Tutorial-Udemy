// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AuraWidgetController.generated.h"

/**
 * 
 */

class UAbilitySystemComponent;
class UAttributeSet;

//Makes it easy to initialize Widget Controllers
USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY();

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS) 
		:PlayerController(PC), PlayerState(PS), AbilitySystemComponent(ASC), AttributeSet(AS) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerController* PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		APlayerState* PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAbilitySystemComponent* AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UAttributeSet* AttributeSet = nullptr;
};

UCLASS()
class AURA_API UAuraWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

		virtual void BroadcastInitialValues();

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
		TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
		TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
		TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
		TObjectPtr<UAttributeSet> AttributeSet;

private:
	
};
