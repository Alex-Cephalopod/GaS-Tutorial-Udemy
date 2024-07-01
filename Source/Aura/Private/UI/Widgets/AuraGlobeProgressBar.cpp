// Copyright Cephalo-Alex


#include "UI/Widgets/AuraGlobeProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/ProgressBar.h"
#include "Components/Image.h"
#include "Components/OverlaySlot.h"
#include "Blueprint/WidgetLayoutLibrary.h"


void UAuraGlobeProgressBar::NativePreConstruct()
{
	Super::NativePreConstruct();

	UpdateBoxSize();
	UpdateBackgroundBrush();
	UpdateGlobeImage(); //Image should be changed to Brush
	UpdateGlobePadding();
	UpdateGlassBrush();
	UpdateGlassPadding();
	UpdateGhostGlobeImage();
}

void UAuraGlobeProgressBar::UpdateBoxSize()
{
	SizeBox_Root->SetWidthOverride(BoxWidth);
	SizeBox_Root->SetHeightOverride(BoxHeight);
}

void UAuraGlobeProgressBar::UpdateBackgroundBrush()
{
	Image_Background->SetBrush(BackgroundBrush);
}

void UAuraGlobeProgressBar::UpdateGlobeImage()
{
	FLinearColor TransparentBG;
	TransparentBG.A = 0;

	FSlateColor Transparent = FSlateColor(TransparentBG);

	FSlateBrush TransparentBrush;
	TransparentBrush.TintColor = Transparent;

	FProgressBarStyle PBarStyle;
	PBarStyle.BackgroundImage = TransparentBrush;
	PBarStyle.FillImage = ProgressBarFillImage;

	ProgressBar_Globe->WidgetStyle = PBarStyle;

}

void UAuraGlobeProgressBar::UpdateGhostGlobeImage()
{
	FLinearColor TransparentBG;
	TransparentBG.A = 0;

	FSlateColor Transparent = FSlateColor(TransparentBG);

	FSlateBrush TransparentBrush;
	TransparentBrush.TintColor = Transparent;

	FProgressBarStyle PBarStyle;
	PBarStyle.BackgroundImage = TransparentBrush;
	PBarStyle.FillImage = GhostBarFillImage;

	ProgressBar_GhostGlobe->WidgetStyle = PBarStyle;
}

void UAuraGlobeProgressBar::UpdateGlobePadding()
{
	UOverlaySlot* AsOverlay = UWidgetLayoutLibrary::SlotAsOverlaySlot(ProgressBar_Globe);

	FMargin PaddingMargin = FMargin(GlobePadding, GlobePadding, GlobePadding, GlobePadding);

	check(AsOverlay);

	AsOverlay->SetPadding(PaddingMargin);
}

void UAuraGlobeProgressBar::UpdateGlassBrush()
{
	Image_Glass->SetBrush(GlassBrush);
}

void UAuraGlobeProgressBar::UpdateGlassPadding()
{
	UOverlaySlot* AsOverlay = UWidgetLayoutLibrary::SlotAsOverlaySlot(Image_Glass);

	FMargin PaddingMargin = FMargin(GlobePadding, GlobePadding, GlobePadding, GlobePadding);

	check(AsOverlay);

	AsOverlay->SetPadding(PaddingMargin);
}

void UAuraGlobeProgressBar::SetProgressBarPercent(float Percent)
{
	if (bGlobeInitialized)
	{
		ProgressBar_Globe->SetPercent(Percent);
		GlobePercentSet(Percent);
	}
	else if (!bGlobeInitialized && Percent > 0.f) {
		bGlobeInitialized = true;

		ProgressBar_Globe->SetPercent(Percent);
		ProgressBar_GhostGlobe->SetPercent(Percent);
		GhostPercentTarget = Percent;
	}
}

void UAuraGlobeProgressBar::SetGhostProgressBarPercent(float Percent)
{
	ProgressBar_GhostGlobe->SetPercent(Percent);
}

void UAuraGlobeProgressBar::GlobePercentSet(float Percent)
{
	//Set a delay of GhostDelay before the ghost globe starts to fill
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAuraGlobeProgressBar::UpdateGhostGlobeImage, GhostDelay, false);

	GhostPercentTarget = Percent;
}

void UAuraGlobeProgressBar::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	float newPercent = FMath::FInterpTo(ProgressBar_GhostGlobe->GetPercent(), GhostPercentTarget, InDeltaTime, GhostFillSpeed);

	SetGhostProgressBarPercent(newPercent);
}


