// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"

#include "STUCharacter.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	explicit ASTUCharacter(const FObjectInitializer& ObjectInitializer);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void Landed(const FHitResult& Hit) override;
	void SetPlayerColor(const FLinearColor& Color);

public:
	UFUNCTION(BlueprintCallable)
	virtual bool IsRunning() const { return false; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	class USTUHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamageVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	class USTUWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Material")
	FName MaterialColorParameter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void OnDeath();
};
