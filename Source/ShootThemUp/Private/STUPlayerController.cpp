// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerController.h"
#include "STURespawnComponent.h"
#include "../ShootThemUpGameModeBase.h"

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
	check(RespawnComponent);
}

void ASTUPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
		InputComponent->BindAction("Pause", IE_Pressed, this, &ASTUPlayerController::OnPause);
}

void ASTUPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (AShootThemUpGameModeBase* const GameMode = GetWorld() ? Cast<AShootThemUpGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr)
		GameMode->OnMatchStateChanged.AddUObject(this, &ASTUPlayerController::OnMatchStateChanged);
}

void ASTUPlayerController::OnPause()
{
	if (AGameModeBase* const GameMode = GetWorld()->GetAuthGameMode())
		GameMode->SetPause(this);
}

FORCEINLINE void ASTUPlayerController::OnMatchStateChanged(ESTUMatchState State)
{
	bShowMouseCursor = State != ESTUMatchState::InProgress;
	if (bShowMouseCursor)
	{
		SetInputMode(FInputModeUIOnly());
	}
	else
	{
		SetInputMode(FInputModeGameOnly());
	}
}
