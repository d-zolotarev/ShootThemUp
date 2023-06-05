// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootThemUpGameModeBase.h"
#include "AIController.h"
#include "STUPlayerState.h"
#include "STUHUD.h"
#include "STUCharacter.h"
#include "STUPlayerController.h"

AShootThemUpGameModeBase::AShootThemUpGameModeBase()
{
	PlayerStateClass = ASTUPlayerState::StaticClass();
	HUDClass = ASTUHUD::StaticClass();
	DefaultPawnClass = ASTUCharacter::StaticClass();
	PlayerControllerClass = ASTUPlayerController::StaticClass();
}

void AShootThemUpGameModeBase::StartPlay()
{
	Super::StartPlay();

	SpawnBots();
	CreateTeams();

	CurrentRound = 1;
	StartRound();
}

UClass* AShootThemUpGameModeBase::GetDefaultPawnClassForController_Implementation(AController* Controller)
{
	return Controller && Controller->IsA<AAIController>() ? AIPawnClass : Super::GetDefaultPawnClassForController_Implementation(Controller);
}

void AShootThemUpGameModeBase::Killed(AController* const KillerController, AController* const VictimController)
{
	if (!(KillerController && VictimController)) return;

	ASTUPlayerState* const KillerPlayerState = Cast<ASTUPlayerState>(KillerController->PlayerState);
	ASTUPlayerState* const VictimPlayerState = Cast<ASTUPlayerState>(VictimController->PlayerState);

	if (KillerPlayerState) KillerPlayerState->AddKill();
	if (VictimPlayerState) VictimPlayerState->AddDeath();
}

void AShootThemUpGameModeBase::SpawnBots()
{
	UWorld* const World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		AAIController* const AIController = World->SpawnActor<AAIController>(AIControllerClass, SpawnParams);
		RestartPlayer(AIController);
	}
}

FORCEINLINE void AShootThemUpGameModeBase::StartRound()
{
	RoundElapsedTime = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AShootThemUpGameModeBase::RoundTimerUpdate, 1.f, true);
}

void AShootThemUpGameModeBase::RoundTimerUpdate()
{
	UE_LOG(LogTemp, Warning, TEXT("Current Round: %d/%d, Elapsed Time: %.0f"), CurrentRound, GameData.RoundsNum, RoundElapsedTime);

	RoundElapsedTime -= GetWorldTimerManager().GetTimerRate(RoundTimerHandle);

	if (FMath::IsNearlyZero(RoundElapsedTime))
	{
		GetWorldTimerManager().ClearTimer(RoundTimerHandle);
		if (CurrentRound != GameData.RoundsNum)
		{
			++CurrentRound;
			ResetPlayers();
			StartRound();
		}
		else
		{
			for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
			{
				if (const ASTUPlayerState* const PlayerState = Cast<ASTUPlayerState>(It->Get()->PlayerState))
				{
					UE_LOG(LogTemp, Warning, TEXT("TeamID: %d, Kills: %d, Deaths: %d"),
						PlayerState->GetTeamID(), PlayerState->GetKillsNum(), PlayerState->GetDeathsNum());
				}
			}

			UE_LOG(LogTemp, Warning, TEXT("GAME OVER"));
		}
	}
}

void AShootThemUpGameModeBase::ResetPlayers()
{
	UWorld* const World = GetWorld();
	if (!World) return;

	for (auto It = World->GetControllerIterator(); It; ++It)
	{
		ResetPlayer(It->Get());
	}
}

void AShootThemUpGameModeBase::ResetPlayer(AController* const Controller)
{
	//Controller->GetPawn()->Reset();
	RestartPlayer(Controller);
	SetPlayerColor(Cast<ASTUCharacter>(Controller->GetPawn()), Cast<ASTUPlayerState>(Controller->PlayerState));
}

void AShootThemUpGameModeBase::CreateTeams()
{
	UWorld* const World = GetWorld();
	if (!World) return;

	int32 TeamID = 1;
	for (auto It = World->GetControllerIterator(); It; ++It)
	{
		//if (!It->IsValid()) continue;

		AController* const Controller = It->Get();

		ASTUPlayerState* const PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(GetTeamColorByID(TeamID));
		
		SetPlayerColor(Cast<ASTUCharacter>(Controller->GetPawn()), PlayerState);

		TeamID = (TeamID == 1) ? 2 : 1;
	}
}

FORCEINLINE FLinearColor AShootThemUpGameModeBase::GetTeamColorByID(int32 TeamID) const
{
	return GameData.TeamColors.IsValidIndex(TeamID - 1) ? GameData.TeamColors[TeamID - 1] : GameData.DefaultTeamColor;
}

FORCEINLINE void AShootThemUpGameModeBase::SetPlayerColor(ASTUCharacter* const Character, const ASTUPlayerState* const PlayerState) const
{
	if (Character && PlayerState)
		Character->SetPlayerColor(PlayerState->GetTeamColor());
}
