// Fill out your copyright notice in the Description page of Project Settings.


#include "STUAIWeaponComponent.h"
#include "STUWeapon.h"

void USTUAIWeaponComponent::Fire()
{
	if (!CanFire()) return;
	
	CurrentWeapon->IsAmmoEmpty() ? NextWeapon() : CurrentWeapon->Fire();
}

void USTUAIWeaponComponent::NextWeapon()
{
	if (!CanEquip()) return;

	int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
	for (; NextIndex != CurrentWeaponIndex; NextIndex = (NextIndex + 1) % Weapons.Num())
	{
		if (!Weapons[NextIndex]->IsAmmoEmpty()) break;
	}

	if (CurrentWeaponIndex != NextIndex)
	{
		CurrentWeaponIndex = NextIndex;
		EquipWeapon(CurrentWeaponIndex);
	}
}
