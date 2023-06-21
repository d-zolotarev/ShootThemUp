// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHUD.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"
#include "STUPlayerHUDWidget.h"
#include "../ShootThemUpGameModeBase.h"

void ASTUHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ASTUHUD::BeginPlay()
{
	Super::BeginPlay();

	Widgets.Add(ESTUMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
	Widgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	Widgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for (auto WidgetPair : Widgets)
	{
		if (UUserWidget* const Widget = WidgetPair.Value)
		{
			Widget->AddToViewport();
			Widget->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (AShootThemUpGameModeBase* const GameMode = GetWorld() ? Cast<AShootThemUpGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr)
		GameMode->OnMatchStateChanged.AddUObject(this, &ASTUHUD::MatchStateChanged);
}

void ASTUHUD::MatchStateChanged(ESTUMatchState State)
{
	if (CurrentWidget) CurrentWidget->SetVisibility(ESlateVisibility::Hidden);

	if (UUserWidget** Widget = Widgets.Find(State))
	{
		CurrentWidget = *Widget;
		CurrentWidget->SetVisibility(ESlateVisibility::Visible);
	}
}
