// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "STUBaseService.h"
#include "STUFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUFindEnemyService : public USTUBaseService

{
	GENERATED_BODY()
	
public:
	USTUFindEnemyService() { NodeName = "Find Enemy"; }

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
