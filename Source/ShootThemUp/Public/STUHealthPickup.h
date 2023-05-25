// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUPickup.h"
#include "STUHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUHealthPickup : public ASTUPickup
{
	GENERATED_BODY()
	
protected:
	virtual bool GivePickupTo(APawn* const PlayerPawn) override;
};
