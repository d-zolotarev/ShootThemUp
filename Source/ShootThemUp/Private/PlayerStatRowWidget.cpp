// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStatRowWidget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

FORCEINLINE void UPlayerStatRowWidget::SetPlayerName(const FString& PlayerName)
{
	SetTextBlockText(PlayerNameTextBlock, PlayerName);
}

FORCEINLINE void UPlayerStatRowWidget::SetKills(int32 Kills)
{
	SetTextBlockText(KillsTextBlock, FString::FromInt(Kills));
}

FORCEINLINE void UPlayerStatRowWidget::SetDeaths(int32 Deaths)
{
	SetTextBlockText(DeathsTextBlock, FString::FromInt(Deaths));
}

FORCEINLINE void UPlayerStatRowWidget::SetTeam(int32 Team, const FLinearColor& TeamColor)
{
	SetTextBlockText(TeamTextBlock, FString::FromInt(Team));
	if (TeamTextBlock) TeamTextBlock->SetColorAndOpacity(TeamColor);
}

FORCEINLINE void UPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool bIsVisible)
{
	if (PlayerIndicatorImage) PlayerIndicatorImage->SetVisibility(bIsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}

FORCEINLINE void UPlayerStatRowWidget::SetTextBlockText(UTextBlock* const TextBlock, const FString& Text)
{
	if (TextBlock) TextBlock->SetText(FText::FromString(Text));
}
