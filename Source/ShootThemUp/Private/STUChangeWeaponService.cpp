// Fill out your copyright notice in the Description page of Project Settings.


#include "STUChangeWeaponService.h"
#include "STUAIWeaponComponent.h"
#include "STUUtils.h"
#include "AIController.h"

void USTUChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (const AAIController* const Controller = OwnerComp.GetAIOwner())
	{
		if (USTUAIWeaponComponent* const WeaponComp = STUUtils::GetComponentByClass<USTUAIWeaponComponent>(Controller->GetPawn()))
		{
			if (FMath::FRand() < Probability)
				WeaponComp->NextWeapon();
		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
