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

protected:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void OnDeath() override;

private:
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Run();
	FORCEINLINE void StopRunning() { bWantsToRun = false; }
	void Fire();


private:
	bool bWantsToRun = false;
	bool bIsMovingForward = false;
};
