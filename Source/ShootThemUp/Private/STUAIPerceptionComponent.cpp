// Fill out your copyright notice in the Description page of Project Settings.


#include "STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercievedActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercievedActors);
	
	if (PercievedActors.Num() == 0) return nullptr;

	const AAIController* const Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const APawn* const Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float MinDistance = MAX_FLT;
	AActor* ClosestActor = nullptr;

	for (AActor* const PercievedActor : PercievedActors)
	{
		const USTUHealthComponent* const HealthComp = STUUtils::GetComponentByClass<USTUHealthComponent>(PercievedActor);

		const APawn* const PercievedPawn = Cast<APawn>(PercievedActor);
		const bool bAreEnemies = PercievedPawn && STUUtils::AreEnemies(Controller, PercievedPawn->Controller);

		if (HealthComp && !HealthComp->IsDead() && bAreEnemies)
		{
			float Distance = FVector::DistSquared(PercievedActor->GetActorLocation(), Pawn->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestActor = PercievedActor;
			}
		}
	}

	return ClosestActor;
}
