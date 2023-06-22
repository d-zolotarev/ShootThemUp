// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameInstance.h"

FORCEINLINE FName USTUGameInstance::GetStartupLevelName() const
{
	if (StartupLevelName.IsNone()) UE_LOG(STUGameInstanceLog, Error, TEXT("StartupLevelName is not set."));
	return StartupLevelName;
}

FORCEINLINE FName USTUGameInstance::GetMainMenuLevelName() const
{
	if (MainMenuLevelName.IsNone()) UE_LOG(STUGameInstanceLog, Error, TEXT("MainMenuLevelName is not set."));
	return MainMenuLevelName;
}
