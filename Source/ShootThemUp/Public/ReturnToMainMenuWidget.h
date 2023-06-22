// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ReturnToMainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UReturnToMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeOnInitialized() override;

protected:
	UPROPERTY(meta = (BindWidget))
	class UButton* ReturnToMainMenuButton;

private:
	UFUNCTION()
	void OnReturnToMainMenu();
};
