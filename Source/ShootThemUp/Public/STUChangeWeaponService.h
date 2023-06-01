// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseService.h"
#include "STUChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUChangeWeaponService : public USTUBaseService
{
	GENERATED_BODY()

public:
	USTUChangeWeaponService() { NodeName = "Change Weapon"; }

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
	float Probability = .5f;
};
