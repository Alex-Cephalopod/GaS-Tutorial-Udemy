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
	UpdateGlobeImage();
	UpdateGlobePadding();
	UpdateGlassBrush();
	UpdateGlassPadding();
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
	ProgressBar_Globe->SetPercent(Percent);
}
