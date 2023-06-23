// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCore.h"
#include "STUMapItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMapItemWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetMapData(const FMapData& NewMapData);
	FMapData GetMapData() const { return MapData; }
	void SetSelected(bool bIsSelected);

public:
	FOnMapSelectedSignature OnMapSelected;

protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* SelectMapButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* MapNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	class UImage* MapPreviewImage;

	UPROPERTY(meta = (BindWidget))
	class UImage* FrameImage;

private:
	UFUNCTION()
	void OnMapItemClicked();

private:
	FMapData MapData;
};
