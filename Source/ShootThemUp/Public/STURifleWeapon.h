// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUWeapon.h"
#include "STURifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTURifleWeapon : public ASTUWeapon
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shooting", meta = (ClampMin = "0.0"))
	float FireRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float DamageAmount;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	class USTUWeaponFXComponent* WeaponFXComponent;

public:
	ASTURifleWeapon();

public:
	virtual void Fire() override;
	virtual void StopFiring() override;

protected:
	virtual void MakeShot() override;

private:
	FTimerHandle FireTimerHandle;

	UPROPERTY()
	class UParticleSystemComponent* MuzzleFlashComp;
};
