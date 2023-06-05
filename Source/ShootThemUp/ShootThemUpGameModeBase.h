// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCore.h"
#include "ShootThemUpGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API AShootThemUpGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AShootThemUpGameModeBase();

public:
	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(class AController* Controller) override;
	void Killed(class AController* const KillerController, class AController* const VictimController);

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<class AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<class APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

private:
	void SpawnBots();
	void StartRound();
	void RoundTimerUpdate();
	void ResetPlayers();
	void ResetPlayer(AController* const Controller);
	void CreateTeams();
	FLinearColor GetTeamColorByID(int32 TeamID) const;
	void SetPlayerColor(class ASTUCharacter* const Character, const class ASTUPlayerState* const PlayerState) const;

private:
	int32 CurrentRound = 1;
	float RoundElapsedTime;
	FTimerHandle RoundTimerHandle;
};
