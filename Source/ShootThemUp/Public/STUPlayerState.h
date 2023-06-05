// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STUPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	ASTUPlayerState();

public:
	FORCEINLINE int32 GetTeamID() const { return TeamID; }
	FORCEINLINE void SetTeamID(int32 ID) { TeamID = ID; }

	FORCEINLINE FLinearColor GetTeamColor() const { return TeamColor; }
	FORCEINLINE void SetTeamColor(const FLinearColor& Color) { TeamColor = Color; }

	FORCEINLINE int32 GetKillsNum() const { return KillsNum; }
	FORCEINLINE void AddKill() { ++KillsNum; }

	FORCEINLINE int32 GetDeathsNum() const { return DeathsNum; }
	FORCEINLINE void AddDeath() { ++DeathsNum; }

private:
	int32 TeamID;
	FLinearColor TeamColor;
	int32 KillsNum;
	int32 DeathsNum;
};
