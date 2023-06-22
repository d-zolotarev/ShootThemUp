// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCore.h"
#include "STUGameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidget))
	class UVerticalBox* PlayerStatBox;

	UPROPERTY(meta = (BindWidget))
	class UButton* RestartLevelButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnRestartLevel();

private:
	void OnMatchStateChanged(ESTUMatchState State);
	void UpdateStat();
};
