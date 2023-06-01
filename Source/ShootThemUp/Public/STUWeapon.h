// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUCore.h"
#include "STUWeapon.generated.h"


UCLASS()
class SHOOTTHEMUP_API ASTUWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUWeapon();

	virtual void Fire();
	virtual void StopFiring();
	void Reload();
	FORCEINLINE bool CanReload() const { return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0; }
	FORCEINLINE bool IsFiring() const { return bIsFiring; }
	FORCEINLINE FWeaponUIData GetUIData() const { return UIData; }
	FORCEINLINE FAmmoData GetCurrentAmmo() const { return CurrentAmmo; }
	bool TryToAddAmmo(int32 ClipsAmount);
	FORCEINLINE bool IsAmmoEmpty() const { return !CurrentAmmo.Infinite && IsClipEmpty() && CurrentAmmo.Clips == 0; }

public:
	FOnClipEmptySignature OnClipEmpty;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class USkeletalMeshComponent* SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting")
	FName MuzzleSocketName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting", meta = (ClampMin = "0.0"))
	float TraceMaxDistance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Shooting", meta = (ClampMin = "0.0"))
	float ScatterAngle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	FAmmoData DefaultAmmo;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	FWeaponUIData UIData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	class UParticleSystem* MuzzleFlash;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void MakeShot();
	FHitResult Hit() const;
	FVector Scatter(const FVector& Direction) const;
	void GetPlayerViewPoint(FVector& Location, FRotator& Rotation) const;
	void GetMuzzleSocketPosition(FQuat& Rotation, FVector& Location) const;
	void GetTraceFromCamera(FVector& TraceStart, FVector& TraceEnd) const;
	FVector HitTraceEnd(const FHitResult& HitResult) const;
	void DecreaseAmmo();
	FORCEINLINE bool IsClipEmpty() const { return CurrentAmmo.Bullets == 0; }

private:
	FORCEINLINE bool IsAmmoFull() const { return CurrentAmmo == DefaultAmmo; }

private:
	FAmmoData CurrentAmmo;
	bool bIsFiring;
};
