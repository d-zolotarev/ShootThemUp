// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUProjectile.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUProjectile();

	FORCEINLINE void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class USphereComponent* CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
	class UProjectileMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon", meta = (ClampMin = "0.0"))
	float LifeSpan;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0"))
	float DamageRadius;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float DamageAmount;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	bool bDoFullDamage;

	UPROPERTY(VisibleAnywhere, Category = "VFX")
	class USTUWeaponFXComponent* WeaponFXComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetController() const;

	FVector ShotDirection;
};
