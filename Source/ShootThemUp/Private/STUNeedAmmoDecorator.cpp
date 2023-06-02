// Fill out your copyright notice in the Description page of Project Settings.


#include "STUNeedAmmoDecorator.h"
#include "AIController.h"
#include "STUUtils.h"
#include "STUAIWeaponComponent.h"

bool USTUNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const AAIController* const Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const USTUAIWeaponComponent* const WeaponComp = STUUtils::GetComponentByClass<USTUAIWeaponComponent>(Controller->GetPawn());
	
	return WeaponComp && WeaponComp->IsWeaponAmmoEmpty(WeaponClass);
}
