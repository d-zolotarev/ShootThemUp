// Copyright Epic Games, Inc. All Rights Reserved.


#include "ShootThemUpGameModeBase.h"
#include "AIController.h"
#include "STUPlayerState.h"
#include "STUHUD.h"
#include "STUCharacter.h"
#include "STUPlayerController.h"
#include "STUUtils.h"
#include "STURespawnComponent.h"
#include "EngineUtils.h"

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

	SetMatchState(ESTUMatchState::InProgress);
}

UClass* AShootThemUpGameModeBase::GetDefaultPawnClassForController_Implementation(AController* Controller)
{
	return Controller && Controller->IsA<AAIController>() ? AIPawnClass : Super::GetDefaultPawnClassForController_Implementation(Controller);
}

bool AShootThemUpGameModeBase::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	if (Super::SetPause(PC, CanUnpauseDelegate))
	{
		SetMatchState(ESTUMatchState::Pause);
		return true;
	}
	
	return false;
}

bool AShootThemUpGameModeBase::ClearPause()
{
	if (Super::ClearPause())
	{
		SetMatchState(ESTUMatchState::InProgress);
		return true;
	}

	return false;
}

void AShootThemUpGameModeBase::Killed(AController* const KillerController, AController* const VictimController)
{
	if (!(KillerController && VictimController)) return;

	ASTUPlayerState* const KillerPlayerState = Cast<ASTUPlayerState>(KillerController->PlayerState);
	ASTUPlayerState* const VictimPlayerState = Cast<ASTUPlayerState>(VictimController->PlayerState);

	if (KillerPlayerState) KillerPlayerState->AddKill();
	if (VictimPlayerState) VictimPlayerState->AddDeath();

	StartRespawn(VictimController);
}

FORCEINLINE void AShootThemUpGameModeBase::RespawnRequest(AController* const Controller)
{
	ResetPlayer(Controller);
}

void AShootThemUpGameModeBase::SpawnBots()
{
	UWorld* const World = GetWorld();
	if (!World) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
	{
		if (AAIController* const AIController = World->SpawnActor<AAIController>(AIControllerClass, SpawnParams))
		{
			if (ASTUPlayerState* const PlayerState = Cast<ASTUPlayerState>(AIController->PlayerState))
			{
				PlayerState->SetPlayerName(FString::Printf(TEXT("Bot %d"), i + 1));
			}
			RestartPlayer(AIController);
		}
	}
}

FORCEINLINE void AShootThemUpGameModeBase::StartRound()
{
	RoundElapsedTime = GameData.RoundTime;
	GetWorldTimerManager().SetTimer(RoundTimerHandle, this, &AShootThemUpGameModeBase::RoundTimerUpdate, 1.f, true);
}

void AShootThemUpGameModeBase::RoundTimerUpdate()
{
	RoundElapsedTime -= GetWorldTimerManager().GetTimerRate(RoundTimerHandle);

	if (FMath::IsNearlyZero(RoundElapsedTime))
	{
		GetWorldTimerManager().ClearTimer(RoundTimerHandle);
		if (++CurrentRound <= GameData.RoundsNum)
		{
			ResetPlayers();
			StartRound();
		}
		else
		{
			GameOver();
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
	RestartPlayer(Controller);
	SetPlayerColor(Cast<ASTUCharacter>(Controller->GetPawn()), Cast<ASTUPlayerState>(Controller->PlayerState));
}

void AShootThemUpGameModeBase::CreateTeams()
{
	const UWorld* const World = GetWorld();
	if (!World) return;

	int32 TeamID = 1;
	for (auto It = World->GetControllerIterator(); It; ++It)
	{
		const AController* const Controller = It->Get();
		if (!Controller) continue;

		ASTUPlayerState* const PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState);
		if (!PlayerState) continue;

		PlayerState->SetTeamID(TeamID);
		PlayerState->SetTeamColor(GetTeamColorByID(TeamID));
		if (Controller->IsPlayerController() && PlayerState->GetPlayerName().IsEmpty())
			PlayerState->SetPlayerName(TEXT("Player"));
		
		SetPlayerColor(Cast<ASTUCharacter>(Controller->GetPawn()), PlayerState);

		TeamID = (TeamID == 1) ? 2 : 1;
	}
}

FORCEINLINE FLinearColor AShootThemUpGameModeBase::GetTeamColorByID(int32 TeamID) const
{
	int32 Index = TeamID - 1;
	return GameData.TeamColors.IsValidIndex(Index) ? GameData.TeamColors[Index] : GameData.DefaultTeamColor;
}

FORCEINLINE void AShootThemUpGameModeBase::SetPlayerColor(ASTUCharacter* const Character, const ASTUPlayerState* const PlayerState) const
{
	if (Character && PlayerState) Character->SetPlayerColor(PlayerState->GetTeamColor());
}

FORCEINLINE void AShootThemUpGameModeBase::StartRespawn(AController* const Controller)
{
	if (Controller && RoundElapsedTime > GameData.MinElapsedTimeForRespawn + GameData.RespawnTime)
	{
		if (USTURespawnComponent* const RespawnComp = Controller->FindComponentByClass<USTURespawnComponent>())
		{
			RespawnComp->Respawn(GameData.RespawnTime);
		}
	}
}

void AShootThemUpGameModeBase::GameOver()
{
	for (auto Pawn : TActorRange<APawn>(GetWorld()))
	{
		if (Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);
		}
	}

	SetMatchState(ESTUMatchState::GameOver);
}

FORCEINLINE void AShootThemUpGameModeBase::SetMatchState(ESTUMatchState NewMatchState)
{
	if (MatchState != NewMatchState)
	{
		MatchState = NewMatchState;
		OnMatchStateChanged.Broadcast(MatchState);
	}
}
