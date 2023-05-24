// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerHUDWidget.h"
#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"

FORCEINLINE float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const auto HealthComponent = GetComponentByClass<USTUHealthComponent>(USTUHealthComponent::StaticClass());
    return HealthComponent ? HealthComponent->GetHealthPercent() : 0.0f;
}

FORCEINLINE bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const auto WeaponComponent = GetComponentByClass<USTUWeaponComponent>(USTUWeaponComponent::StaticClass());
    return WeaponComponent && WeaponComponent->GetCurrentWeaponUIData(UIData);
}

FORCEINLINE bool USTUPlayerHUDWidget::GetCurrentWeaponAmmo(FAmmoData& AmmoData) const
{
    const auto WeaponComponent = GetComponentByClass<USTUWeaponComponent>(USTUWeaponComponent::StaticClass());
    return WeaponComponent && WeaponComponent->GetCurrentWeaponAmmo(AmmoData);
}

FORCEINLINE bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = GetComponentByClass<USTUHealthComponent>(USTUHealthComponent::StaticClass());
    return HealthComponent && !HealthComponent->IsDead();
}

FORCEINLINE bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}
