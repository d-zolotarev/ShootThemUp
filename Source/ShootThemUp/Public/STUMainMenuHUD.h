// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STUMainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

protected:
	virtual void BeginPlay() override;
};
