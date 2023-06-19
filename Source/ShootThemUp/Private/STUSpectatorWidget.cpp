// Fill out your copyright notice in the Description page of Project Settings.


#include "STUSpectatorWidget.h"
#include "STURespawnComponent.h"
#include "STUUtils.h"

bool USTUSpectatorWidget::GetRespawnTime(int32& RespawnTimeElapsed) const
{
	const USTURespawnComponent* const RespawnComp = STUUtils::GetComponentByClass<USTURespawnComponent>(GetOwningPlayer());
	if (!(RespawnComp && RespawnComp->IsRespawnInProgress())) return false;

	RespawnTimeElapsed = RespawnComp->GetRespawnCountDown();

	return true;
}
