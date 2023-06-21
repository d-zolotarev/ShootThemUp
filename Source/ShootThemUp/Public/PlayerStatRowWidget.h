// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API UPlayerStatRowWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetPlayerName(const FString& PlayerName);
	void SetKills(int32 Kills);
	void SetDeaths(int32 Deaths);
	void SetTeam(int32 Team, const FLinearColor& TeamColor);
	void SetPlayerIndicatorVisibility(bool bIsVisible);

protected:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* PlayerNameTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* KillsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* DeathsTextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamTextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* PlayerIndicatorImage;

private:
	void SetTextBlockText(UTextBlock* const TextBlock, const FString& Text);
};
