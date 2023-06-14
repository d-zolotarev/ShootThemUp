// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameDataWidget.h"
#include "../ShootThemUpGameModeBase.h"
#include "STUPlayerState.h"

int32 USTUGameDataWidget::GetCurrentRound() const
{
	const AShootThemUpGameModeBase* const GameMode = GetGameMode();
	return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 USTUGameDataWidget::GetTotalRounds() const
{
	const AShootThemUpGameModeBase* const GameMode = GetGameMode();
	return GameMode ? GameMode->GetTotalRounds() : 0;
}

float USTUGameDataWidget::GetRoundElapsedTime() const
{
	const AShootThemUpGameModeBase* const GameMode = GetGameMode();
	return GameMode ? GameMode->GetRoundElapsedTime() : 0.f;
}

int32 USTUGameDataWidget::GetKillsNum() const
{
	const ASTUPlayerState* const PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetKillsNum() : 0;
}

int32 USTUGameDataWidget::GetDeathsNum() const
{
	const ASTUPlayerState* const PlayerState = GetPlayerState();
	return PlayerState ? PlayerState->GetDeathsNum() : 0;
}

FORCEINLINE const AShootThemUpGameModeBase* const USTUGameDataWidget::GetGameMode() const
{
	return GetWorld() ? Cast<AShootThemUpGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

FORCEINLINE const ASTUPlayerState* const USTUGameDataWidget::GetPlayerState() const
{
	return Cast<ASTUPlayerState>(GetOwningPlayerState());
}
