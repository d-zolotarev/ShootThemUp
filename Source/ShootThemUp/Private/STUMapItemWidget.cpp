// Fill out your copyright notice in the Description page of Project Settings.


#include "STUMapItemWidget.h"
#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

void USTUMapItemWidget::SetMapData(const FMapData& NewMapData)
{
	MapData = NewMapData;

	if (MapNameTextBlock) MapNameTextBlock->SetText(FText::FromName(MapData.MapDisplayName));

	if (MapPreviewImage) MapPreviewImage->SetBrushFromTexture(MapData.MapThumbnail);
}

FORCEINLINE void USTUMapItemWidget::SetSelected(bool bIsSelected)
{
	if (FrameImage)
		FrameImage->SetVisibility(bIsSelected ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

void USTUMapItemWidget::NativeOnInitialized()
{
	if (SelectMapButton)
		SelectMapButton->OnClicked.AddDynamic(this, &USTUMapItemWidget::OnMapItemClicked);
}

FORCEINLINE void USTUMapItemWidget::OnMapItemClicked()
{
	OnMapSelected.Broadcast(MapData);
}
