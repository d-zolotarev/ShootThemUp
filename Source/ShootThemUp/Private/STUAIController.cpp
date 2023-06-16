// Fill out your copyright notice in the Description page of Project Settings.


#include "STUAIController.h"
#include "STUAICharacter.h"
#include "STUAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "STURespawnComponent.h"

ASTUAIController::ASTUAIController() : FocusOnKeyName{"EnemyActor"}
{
	STUPerceptionComponent = CreateDefaultSubobject<USTUAIPerceptionComponent>("STUPerceptionComponent");
	check(STUPerceptionComponent);
	SetPerceptionComponent(*STUPerceptionComponent);

	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
	check(RespawnComponent);

	bWantsPlayerState = true;
}

void ASTUAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	SetFocus(GetFocusOnActor());
}

void ASTUAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (ASTUAICharacter* const AICharacter = Cast<ASTUAICharacter>(InPawn))
	{
		RunBehaviorTree(AICharacter->BehaviorTree);
	}
}

FORCEINLINE AActor* ASTUAIController::GetFocusOnActor() const
{
	const UBlackboardComponent* const BlackboardComp = GetBlackboardComponent();
	return (BlackboardComp) ? Cast<AActor>(BlackboardComp->GetValueAsObject(FocusOnKeyName)) : nullptr;
}
