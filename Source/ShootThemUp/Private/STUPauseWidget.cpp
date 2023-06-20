// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPauseWidget.h"
#include "GameFramework/GameModeBase.h"
#include "Components/Button.h"

bool USTUPauseWidget::Initialize()
{
	const bool SuperInit = Super::Initialize();

	if (ContinueButton)
	{
		ContinueButton->OnClicked.AddDynamic(this, &USTUPauseWidget::OnClearPause);
	}

	return SuperInit;
}

void USTUPauseWidget::OnClearPause()
{
	AGameModeBase* const GameMode = GetWorld() ? GetWorld()->GetAuthGameMode() : nullptr;
	if (GameMode) GameMode->ClearPause();
}
