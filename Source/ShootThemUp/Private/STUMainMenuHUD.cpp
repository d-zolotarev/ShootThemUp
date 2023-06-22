// Fill out your copyright notice in the Description page of Project Settings.


#include "STUMainMenuHUD.h"
#include "STUMainMenuWidget.h"

void ASTUMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (UUserWidget* const MainMenuWidget = CreateWidget<USTUMainMenuWidget>(GetWorld(), MainMenuWidgetClass))
		MainMenuWidget->AddToViewport();
}
