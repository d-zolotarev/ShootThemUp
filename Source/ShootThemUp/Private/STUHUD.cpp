// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.h"

void ASTUHUD::DrawHUD()
{
	Super::DrawHUD();

	//DrawCrosshair();
}

void ASTUHUD::BeginPlay()
{
	Super::BeginPlay();

	if (auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass))
		PlayerHUDWidget->AddToViewport();
}

void ASTUHUD::DrawCrosshair()
{
	const float CenterX = Canvas->SizeX * .5f;
	const float CenterY = Canvas->SizeY * .5f;
	const float HalfLineSize = 10.f;

	DrawLine(CenterX - HalfLineSize, CenterY, CenterX + HalfLineSize, CenterY, FLinearColor::Red, 2.f);
	DrawLine(CenterX, CenterY - HalfLineSize, CenterX, CenterY + HalfLineSize, FLinearColor::Red, 2.f);
}
