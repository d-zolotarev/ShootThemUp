// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUWeapon.h"
#include "STULauncherWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTULauncherWeapon : public ASTUWeapon
{
	GENERATED_BODY()

public:
	ASTULauncherWeapon() { DefaultAmmo = FAmmoData{1, 10, false}; }

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASTUProjectile> ProjectileClass;

	virtual void MakeShot() override;

};
