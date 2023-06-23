// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STUCore.h"
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
	FMapData GetStartupLevel() const { return StartupLevel; }
	void SetStartupLevel(const FMapData& NewStartupLevel) { StartupLevel = NewStartupLevel; }
	FName GetMainMenuLevelName() const;
	TArray<FMapData> GetMapsData() const { return MapsData; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TArray<FMapData> MapsData;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName MainMenuLevelName{"MainMenuLevel"};

private:
	FMapData StartupLevel;
};
