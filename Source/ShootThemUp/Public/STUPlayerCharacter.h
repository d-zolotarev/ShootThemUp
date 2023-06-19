// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUCharacter.h"
#include "STUPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API ASTUPlayerCharacter : public ASTUCharacter
{
	GENERATED_BODY()

public:
	explicit ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer);

public:
	virtual bool IsRunning() const override { return bWantsToRun && bIsMovingForward && !GetVelocity().IsNearlyZero(); }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera Settings | Camera Boom")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Camera Setting | Camera Options")
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	class USphereComponent* CameraCollisionComponent;

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnDeath() override;
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UFUNCTION()
	void OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Run();
	FORCEINLINE void StopRunning() { bWantsToRun = false; }
	void Fire();
	void CheckCameraOverlap();

private:
	bool bWantsToRun = false;
	bool bIsMovingForward = false;
};
