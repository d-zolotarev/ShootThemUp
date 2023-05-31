// Fill out your copyright notice in the Description page of Project Settings.


#include "STUNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

USTUNextLocationTask::USTUNextLocationTask() : Radius{1000.f}, bSelfCenter{true}
{
	NodeName = "Next Location";
}

EBTNodeResult::Type USTUNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const AAIController* const Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* const BlackboardComp = OwnerComp.GetBlackboardComponent();
	if (!Controller || !BlackboardComp) return EBTNodeResult::Failed;

	APawn* const Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	UNavigationSystemV1* const NavSys = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavSys) return EBTNodeResult::Failed;

	FVector Location = Pawn->GetActorLocation();
	
	if (!bSelfCenter)
	{
		const AActor* const CenterActor = Cast<AActor>(BlackboardComp->GetValueAsObject(CenterActorKey.SelectedKeyName));
		if (!CenterActor) return EBTNodeResult::Failed;
		Location = CenterActor->GetActorLocation();
	}
	
	FNavLocation NavLocation;
	if (!NavSys->GetRandomReachablePointInRadius(Location, Radius, NavLocation))
		return EBTNodeResult::Failed;

	BlackboardComp->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);

	return EBTNodeResult::Succeeded;
}
