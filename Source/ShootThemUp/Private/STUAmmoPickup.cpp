// Fill out your copyright notice in the Description page of Project Settings.


#include "STUAmmoPickup.h"
#include "STUWeaponComponent.h"
#include "STUHealthComponent.h"
#include "STUUtils.h"

bool ASTUAmmoPickup::GivePickupTo(APawn* const PlayerPawn)
{
    const USTUHealthComponent* const HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead()) return false;

    USTUWeaponComponent* const WeaponComponent = STUUtils::GetComponentByClass<USTUWeaponComponent>(PlayerPawn);
    if (!WeaponComponent) return false;

    return WeaponComponent->TryToAddAmmo(ClipsAmount, WeaponClass);
}
