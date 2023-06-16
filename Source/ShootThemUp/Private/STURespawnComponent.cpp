// Fill out your copyright notice in the Description page of Project Settings.


#include "STURespawnComponent.h"
#include "../ShootThemUpGameModeBase.h"

// Sets default values for this component's properties
USTURespawnComponent::USTURespawnComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void USTURespawnComponent::Respawn(int32 RespawnTime)
{
	RespawnCountDown = RespawnTime;
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &USTURespawnComponent::RespawnTimerUpdate, 1.f, true);
}


// Called when the game starts
void USTURespawnComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USTURespawnComponent::RespawnTimerUpdate()
{
	if (--RespawnCountDown == 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);	
		if (AShootThemUpGameModeBase* const GameMode = Cast<AShootThemUpGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->RespawnRequest(Cast<AController>(GetOwner()));
		}
	}
}
