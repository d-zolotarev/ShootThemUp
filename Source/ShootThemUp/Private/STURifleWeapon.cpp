// Fill out your copyright notice in the Description page of Project Settings.


#include "STURifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "STUCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "STUWeaponFXComponent.h"
#include "Particles/ParticleSystemComponent.h"


ASTURifleWeapon::ASTURifleWeapon() : FireRate{600.f}, DamageAmount{10.f}, MuzzleFlashComp {nullptr}
{
	DefaultAmmo = FAmmoData{30, 10, false};

	WeaponFXComponent = CreateDefaultSubobject<USTUWeaponFXComponent>("WeaponFXComponent");
	check(WeaponFXComponent);
}

void ASTURifleWeapon::Fire()
{
	if (MuzzleFlash && !MuzzleFlashComp)
	{
		MuzzleFlashComp = UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetRootComponent(), MuzzleSocketName, FVector::ZeroVector,
			FRotator::ZeroRotator, EAttachLocation::SnapToTarget, false, EPSCPoolMethod::None, false);
	}

	if (MuzzleFlashComp) MuzzleFlashComp->ActivateSystem();

	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ASTURifleWeapon::MakeShot, 60.f / FireRate, true);
	Super::Fire();
}

void ASTURifleWeapon::StopFiring()
{
	if (MuzzleFlashComp) MuzzleFlashComp->DeactivateSystem();
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

	if (const FHitResult HitResult = Hit(); HitResult.bBlockingHit)
	{
		TSubclassOf<UDamageType> DamageType;
		UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), DamageAmount, HitResult.ImpactNormal, HitResult,
			GetOwner()->GetInstigatorController(), this, DamageType);
		UE_LOG(LogTemp, Warning, TEXT("Hit %s"), *HitResult.BoneName.ToString());
		WeaponFXComponent->PlayImpactFX(HitResult);
	}

	DecreaseAmmo();
}
