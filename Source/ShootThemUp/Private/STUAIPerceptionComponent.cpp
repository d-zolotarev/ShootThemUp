// Fill out your copyright notice in the Description page of Project Settings.


#include "STUAIPerceptionComponent.h"
#include "AIController.h"
#include "STUUtils.h"
#include "STUHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* USTUAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	
	if (PercieveActors.Num() == 0) return nullptr;

	const AAIController* const Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const APawn* const Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float MinDistance = MAX_FLT;
	AActor* ClosestActor = nullptr;

	for (AActor* const Actor : PercieveActors)
	{
		const USTUHealthComponent* const HealthComp = STUUtils::GetComponentByClass<USTUHealthComponent>(Actor);
		if (HealthComp && !HealthComp->IsDead())
		{
			float Distance = FVector::DistSquared(Actor->GetActorLocation(), Pawn->GetActorLocation());
			if (Distance < MinDistance)
			{
				MinDistance = Distance;
				ClosestActor = Actor;
			}
		}
	}

	return ClosestActor;
}
