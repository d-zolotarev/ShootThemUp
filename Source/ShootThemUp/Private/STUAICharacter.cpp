// Fill out your copyright notice in the Description page of Project Settings.


#include "STUAICharacter.h"
#include "STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUAIWeaponComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BrainComponent.h"

ASTUAICharacter::ASTUAICharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<USTUAIWeaponComponent>("WeaponComponent"))
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTUAIController::StaticClass();

	bUseControllerRotationYaw = false;
	
	UCharacterMovementComponent* const MovementComponent = GetCharacterMovement();
	check(MovementComponent);
	MovementComponent->bUseControllerDesiredRotation = true;
	MovementComponent->RotationRate = FRotator(0.f, 200.f, 0.f);
}

void ASTUAICharacter::OnDeath()
{
	Super::OnDeath();

	const AAIController* const AIController = Cast<AAIController>(Controller);
	if (AIController && AIController->BrainComponent)
	{
		AIController->BrainComponent->Cleanup();
	}
}
