// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
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

protected:
	virtual void NativeOnInitialized() override;

private:
	UFUNCTION()
	void OnStartGame();
};
