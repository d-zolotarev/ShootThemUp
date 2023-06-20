// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUCore.h"
#include "STUPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASTUPlayerController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class USTURespawnComponent* RespawnComponent;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	void OnPause();
	void OnMatchStateChanged(ESTUMatchState State);
};
