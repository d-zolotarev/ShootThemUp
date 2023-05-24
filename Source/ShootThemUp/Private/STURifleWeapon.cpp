// Fill out your copyright notice in the Description page of Project Settings.


#include "STURifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "STUCharacter.h"
#include "Kismet/GameplayStatics.h"


ASTURifleWeapon::ASTURifleWeapon() : FireRate{600.f}, DamageAmount{10.f}
{
	DefaultAmmo = FAmmoData{30, 10, false};
}

void ASTURifleWeapon::Fire()
{
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASTURifleWeapon::MakeShot, 60.f / FireRate, true);
	Super::Fire();
}

void ASTURifleWeapon::StopFiring()
{
	Super::StopFiring();
	GetWorldTimerManager().ClearTimer(FireTimerHandle);
}

void ASTURifleWeapon::MakeShot()
{
	if (IsAmmoEmpty())
	{
		StopFiring();
		return;
	}

	const FHitResult HitResult = Hit();

	if (HitResult.bBlockingHit)
	{
		TSubclassOf<UDamageType> DamageType;
		UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), DamageAmount, HitResult.ImpactNormal, HitResult,
			GetOwner()->GetInstigatorController(), this, DamageType);
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.BoneName.ToString());
	}
	DrawDebugLine(GetWorld(), HitResult.TraceStart, HitTraceEnd(HitResult), FColor::Red, false, 3.f, 0U, 3.f);
	DecreaseAmmo();
}
