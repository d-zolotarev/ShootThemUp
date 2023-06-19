// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerHUDWidget.h"
#include "STUHealthComponent.h"
#include "STUWeaponComponent.h"
#include "STUUtils.h"

FORCEINLINE float USTUPlayerHUDWidget::GetHealthPercent() const
{
    const USTUHealthComponent* const HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent ? HealthComponent->GetHealthPercent() : 0.0f;
}

FORCEINLINE bool USTUPlayerHUDWidget::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
    const USTUWeaponComponent *const WeaponComponent = STUUtils::GetComponentByClass<USTUWeaponComponent>(GetOwningPlayerPawn());
    return WeaponComponent && WeaponComponent->GetCurrentWeaponUIData(UIData);
}

FORCEINLINE bool USTUPlayerHUDWidget::GetCurrentWeaponAmmo(FAmmoData& AmmoData) const
{
    const USTUWeaponComponent* const WeaponComponent = STUUtils::GetComponentByClass<USTUWeaponComponent>(GetOwningPlayerPawn());
    return WeaponComponent && WeaponComponent->GetCurrentWeaponAmmo(AmmoData);
}

FORCEINLINE bool USTUPlayerHUDWidget::IsPlayerAlive() const
{
    const USTUHealthComponent* const HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(GetOwningPlayerPawn());
    return HealthComponent && !HealthComponent->IsDead();
}

FORCEINLINE bool USTUPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool USTUPlayerHUDWidget::Initialize()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &USTUPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }

    return Super::Initialize();
}

FORCEINLINE void USTUPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0) OnTakeDamage();
}

FORCEINLINE void USTUPlayerHUDWidget::OnNewPawn(APawn* Pawn)
{
    USTUHealthComponent* const HealthComponent = STUUtils::GetComponentByClass<USTUHealthComponent>(Pawn);
    if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
        HealthComponent->OnHealthChanged.AddUObject(this, &USTUPlayerHUDWidget::OnHealthChanged);
}
