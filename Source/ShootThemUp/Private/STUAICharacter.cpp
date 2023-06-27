// Fill out your copyright notice in the Description page of Project Settings.


#include "STUAICharacter.h"
#include "STUAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "STUAIWeaponComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BrainComponent.h"
#include "STUHealthComponent.h"
#include "Components/WidgetComponent.h"
#include "STUHealthBarWidget.h"

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

	HealthBarWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthBarWidgetComponent");
	check(HealthBarWidgetComponent);
	HealthBarWidgetComponent->SetupAttachment(GetRootComponent());
	HealthBarWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
	HealthBarWidgetComponent->SetDrawAtDesiredSize(true);
}

void ASTUAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetWorld() && GetWorld()->GetFirstPlayerController() && GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
	{
		const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
		const float DistSquared = FVector::DistSquared(PlayerLocation, GetActorLocation());
		HealthBarWidgetComponent->SetVisibility(DistSquared < FMath::Square(HealthVisibilityDistance), true);
	}
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

void ASTUAICharacter::BeginPlay()
{
	Super::BeginPlay();

	if (HealthComponent) HealthComponent->OnHealthChanged.AddUObject(this, &ASTUAICharacter::OnHealthChanged);
}

FORCEINLINE void ASTUAICharacter::OnHealthChanged(float Health, float DeltaHealth)
{
	if (USTUHealthBarWidget* const HealthBarWidget = Cast<USTUHealthBarWidget>(HealthBarWidgetComponent->GetUserWidgetObject()))
	{
		HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
	}
}
