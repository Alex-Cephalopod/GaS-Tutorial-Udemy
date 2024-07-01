// Copyright Cephalo-Alex

#pragma once

#include "CoreMinimal.h"
#include "UI/Widgets/AuraUserWidget.h"
//#include "Styling/SlateBrush.h"
#include "AuraGlobeProgressBar.generated.h"

/**
 * 
 */

class USizeBox;
class UImage;
class UProgressBar;
//struct FSlateBrush; 

UCLASS()
class AURA_API UAuraGlobeProgressBar : public UAuraUserWidget
{
	GENERATED_BODY()

public:

	virtual void NativePreConstruct() override;

	UFUNCTION()
	void UpdateBoxSize();

	UFUNCTION()
	void UpdateBackgroundBrush();

	UFUNCTION()
	void UpdateGlobeImage();

	UFUNCTION()
	void UpdateGhostGlobeImage();

	UFUNCTION()
	void UpdateGlobePadding();

	UFUNCTION()
	void UpdateGlassBrush();

	UFUNCTION()
	void UpdateGlassPadding();

	UFUNCTION(BlueprintCallable)
	void SetProgressBarPercent(float Percent);

	UFUNCTION(BlueprintCallable)
	void SetGhostProgressBarPercent(float Percent);

	UFUNCTION()
	void GlobePercentSet(float Percent);

protected:

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		USizeBox* SizeBox_Root;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Image_Background;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* ProgressBar_Globe;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UProgressBar* ProgressBar_GhostGlobe;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UImage* Image_Glass;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		float BoxWidth;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		float BoxHeight;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		FSlateBrush BackgroundBrush;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		FSlateBrush ProgressBarFillImage;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		FSlateBrush GhostBarFillImage;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		float GlobePadding;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		FSlateBrush GlassBrush;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		float GhostPercentTarget;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		float GhostDelay = 0.2f;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		float GhostFillSpeed = 1.f;

	UPROPERTY(EditAnywhere, Category = "Globe Properties")
		bool bGlobeInitialized = false;

private:
	
};
