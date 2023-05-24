// Fill out your copyright notice in the Description page of Project Settings.


#include "STULauncherWeapon.h"
#include "STUProjectile.h"

void ASTULauncherWeapon::MakeShot()
{
	if (IsAmmoEmpty()) return;

	FQuat MuzzleSocketRotation;
	FVector MuzzleSocketLocation;
	GetMuzzleSocketPosition(MuzzleSocketRotation, MuzzleSocketLocation);

	const FHitResult HitResult = Hit();
	const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd;
	const FVector Direction = (EndPoint - MuzzleSocketLocation).GetSafeNormal();

	const FTransform SpawnTransform(FRotator::ZeroRotator, MuzzleSocketLocation);
	ASTUProjectile* Projectile = GetWorld()->SpawnActorDeferred<ASTUProjectile>(ProjectileClass, SpawnTransform);
	if (Projectile)
	{
		Projectile->SetOwner(GetOwner());
		Projectile->SetShotDirection(Direction);
		Projectile->FinishSpawning(SpawnTransform);
	}

	DecreaseAmmo();
}
