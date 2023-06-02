// Fill out your copyright notice in the Description page of Project Settings.


#include "STUEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void USTUEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
	AActor* const QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());
	
	const UBlackboardComponent* const BlackboardComp = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!BlackboardComp) return;

	const AActor* const ContextActor = Cast<AActor>(BlackboardComp->GetValueAsObject(EnemyActorKeyName));

	UEnvQueryItemType_Actor::SetContextHelper(ContextData, ContextActor);
}
