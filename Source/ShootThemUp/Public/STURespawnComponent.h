// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STURespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTURespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTURespawnComponent();

public:
	void Respawn(int32 RespawnTime);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	void RespawnTimerUpdate();

private:
	FTimerHandle RespawnTimerHandle;
	int32 RespawnCountDown = 0;
};
