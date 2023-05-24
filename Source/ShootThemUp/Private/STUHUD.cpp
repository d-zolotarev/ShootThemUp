// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.h"

void ASTUHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ASTUHUD::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass))
		PlayerHUDWidget->AddToViewport();
}
