// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthPercentDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "STUHealthComponent.h"

bool USTUHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* const Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const USTUHealthComponent* const HealthComp = STUUtils::GetComponentByClass<USTUHealthComponent>(Controller->GetPawn());
	if (!HealthComp || HealthComp->IsDead()) return false;

	return HealthComp->GetHealthPercent() <= HealthPercent;
}
