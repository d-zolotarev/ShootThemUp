// Fill out your copyright notice in the Description page of Project Settings.


#include "STUFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "STUAIPerceptionComponent.h"


void USTUFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const AAIController* const Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* const BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (Controller && BlackboardComp)
	{
		const USTUAIPerceptionComponent* const PerceptionComponent = STUUtils::GetComponentByClass<USTUAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			BlackboardComp->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
