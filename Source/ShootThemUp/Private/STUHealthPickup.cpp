// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthPickup.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"

bool ASTUHealthPickup::GivePickupTo(APawn* const PlayerPawn)
{
    USTUHealthComponent *const HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(PlayerPawn);

    return HealthComponent ? HealthComponent->TryToAddHealth(HealthAmount) : false;
}
