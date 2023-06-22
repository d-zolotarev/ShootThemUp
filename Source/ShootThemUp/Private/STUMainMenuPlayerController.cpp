// Fill out your copyright notice in the Description page of Project Settings.


#include "STUMainMenuPlayerController.h"

void ASTUMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
