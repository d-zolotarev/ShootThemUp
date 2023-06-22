// Fill out your copyright notice in the Description page of Project Settings.


#include "STUMainMenuGameModeBase.h"
#include "STUMainMenuPlayerController.h"
#include "STUMainMenuHUD.h"

ASTUMainMenuGameModeBase::ASTUMainMenuGameModeBase()
{
	PlayerControllerClass = ASTUMainMenuPlayerController::StaticClass();
	HUDClass = ASTUMainMenuHUD::StaticClass();
}
