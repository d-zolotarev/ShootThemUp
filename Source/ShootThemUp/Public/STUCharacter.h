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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera Settings | Camera Boom")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera Setting | Camera Options")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	class USTUHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Health")
	class UTextRenderComponent* HealthTextComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animation")
	class UAnimMontage* DeathAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamageVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	FVector2D LandedDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	class USTUWeaponComponent* WeaponComponent;

public:
	UFUNCTION(BlueprintCallable)
	FORCEINLINE bool IsRunning() const { return bWantsToRun && bIsMovingForward && !GetVelocity().IsNearlyZero(); }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Landed(const FHitResult& Hit) override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Run();
	FORCEINLINE void StopRunning() { bWantsToRun = false; }
	void OnHealthChanged(float Value, float Delta);
	void OnDeath();
	void Fire();

private:
	bool bWantsToRun;
	bool bIsMovingForward;
};
