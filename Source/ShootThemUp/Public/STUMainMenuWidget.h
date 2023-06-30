// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCore.h"
#include "STUMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	class UButton* QuitGameButton;

	UPROPERTY(meta = (BindWidget))
	class UHorizontalBox* MapsHorizontalBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<class USTUMapItemWidget> MapItemWidgetClass;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* LoadingAnimation;

protected:
	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

private:
	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

private:
	void InitMapItems();
	void OnMapSelected(const FMapData& SelectedMapData);
	class USTUGameInstance* GetGameInstance() const;

private:
	UPROPERTY()
	TArray<class USTUMapItemWidget*> MapItemWidgets;
};
