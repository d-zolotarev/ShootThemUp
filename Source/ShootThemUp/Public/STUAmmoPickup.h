// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUPickup.h"
#include "STUAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUAmmoPickup : public ASTUPickup
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Pickup", meta = (ClampMin = "1", ClampMax = "10"))
	int32 ClipsAmount = 10;

	UPROPERTY(EditAnywhere, BlueprintReadwrite, Category = "Pickup")
	TSubclassOf<class ASTUWeapon> WeaponClass;

protected:
	virtual bool GivePickupTo(APawn* const PlayerPawn) override;
};
