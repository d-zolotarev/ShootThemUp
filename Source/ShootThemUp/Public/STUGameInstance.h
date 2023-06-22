// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUGameInstance.generated.h"

DECLARE_LOG_CATEGORY_CLASS(STUGameInstanceLog, All, All)

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	FName GetStartupLevelName() const;
	FName GetMainMenuLevelName() const;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName StartupLevelName{NAME_None};

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MainMenuLevelName{"MainMenuLevel"};
};
