// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUGameDataWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUGameDataWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetCurrentRound() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetTotalRounds() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	float GetRoundElapsedTime() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetKillsNum() const;

	UFUNCTION(BlueprintCallable, Category = "UI")
	int32 GetDeathsNum() const;

private:
	const class AShootThemUpGameModeBase* const GetGameMode() const;
	const class ASTUPlayerState* const GetPlayerState() const;
};
