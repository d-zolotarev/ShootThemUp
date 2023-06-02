// Fill out your copyright notice in the Description page of Project Settings.


#include "EnvQueryTest_PickupCouldBeTaken.h"
#include "STUPickup.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"

UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}

void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
	BoolValue.BindData(QueryInstance.Owner.Get(), QueryInstance.QueryID);
	bool bWantsBeTakeble = BoolValue.GetValue();

	for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		const ASTUPickup* const Pickup = Cast<ASTUPickup>(GetItemActor(QueryInstance, It.GetIndex()));
		if (!Pickup) continue;

		It.SetScore(TestPurpose, FilterType, Pickup->CouldBeTaken(), bWantsBeTakeble);
	}
}
