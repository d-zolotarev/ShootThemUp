// Fill out your copyright notice in the Description page of Project Settings.


#include "STUFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "STUWeaponComponent.h"
#include "STUUtils.h"


void USTUFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (const AAIController* const Controller = OwnerComp.GetAIOwner())
	{
		if (USTUWeaponComponent* const WeaponComp = STUUtils::GetComponentByClass<USTUWeaponComponent>(Controller->GetPawn()))
		{
			const UBlackboardComponent* const BlackboardComp = OwnerComp.GetBlackboardComponent();
			BlackboardComp && BlackboardComp->GetValueAsObject(EnemyActorKey.SelectedKeyName) ? WeaponComp->Fire() : WeaponComp->StopFiring();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
