// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerHUDWidget.h"
#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"

FORCEINLINE float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = GetComponentByClass<USTUHealthComponent>(USTUHealthComponent::StaticClass());
    return HealthComponent ? HealthComponent->GetHealthPercent() : 0.0f;
}

FORCEINLINE bool USTUPlayerHUDWidget::GetWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = GetComponentByClass<USTUWeaponComponent>(USTUWeaponComponent::StaticClass());
    return WeaponComponent ? WeaponComponent->GetWeaponUIData(UIData) : false;
}

FORCEINLINE bool USTUPlayerHUDWidget::GetWeaponAmmo(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = GetComponentByClass<USTUWeaponComponent>(USTUWeaponComponent::StaticClass());
    return WeaponComponent ? WeaponComponent->GetWeaponAmmo(AmmoData) : false;
}
