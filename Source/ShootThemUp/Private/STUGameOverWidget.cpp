// Fill out your copyright notice in the Description page of Project Settings.


#include "STUGameOverWidget.h"
#include "../ShootThemUpGameModeBase.h"
#include "STUPlayerState.h"
#include "PlayerStatRowWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

FORCEINLINE void USTUGameOverWidget::OnMatchStateChanged(ESTUMatchState State)
{
	if (State == ESTUMatchState::GameOver)
	{
		UpdateStat();
	}
}

void USTUGameOverWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (AShootThemUpGameModeBase* const GameMode = GetWorld() ? Cast<AShootThemUpGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr)
		GameMode->OnMatchStateChanged.AddUObject(this, &USTUGameOverWidget::OnMatchStateChanged);

	if (RestartLevelButton) RestartLevelButton->OnClicked.AddDynamic(this, &USTUGameOverWidget::OnRestartLevel);
}

void USTUGameOverWidget::UpdateStat()
{
	if (!(GetWorld() && PlayerStatBox)) return;

	PlayerStatBox->ClearChildren();

	for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{	
		if (const AController* const Controller = It->Get())
		{
			if (const ASTUPlayerState* const PlayerState = Cast<ASTUPlayerState>(Controller->PlayerState))
			{
				if (UPlayerStatRowWidget* const PlayerStatRowWidget = CreateWidget<UPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass))
				{
					PlayerStatRowWidget->SetPlayerName(PlayerState->GetPlayerName());
					PlayerStatRowWidget->SetKills(PlayerState->GetKillsNum());
					PlayerStatRowWidget->SetDeaths(PlayerState->GetDeathsNum());
					PlayerStatRowWidget->SetTeam(PlayerState->GetTeamID(), PlayerState->GetTeamColor());
					PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

					PlayerStatBox->AddChild(PlayerStatRowWidget);
				}
			}
		}
	}
}

FORCEINLINE void USTUGameOverWidget::OnRestartLevel()
{
	UGameplayStatics::OpenLevel(GetWorld(), FName(UGameplayStatics::GetCurrentLevelName(GetWorld())));
}