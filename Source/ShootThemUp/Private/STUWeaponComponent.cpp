// Fill out your copyright notice in the Description page of Project Settings.


#include "STUWeaponComponent.h"
#include "STUWeapon.h"
#include "STUCharacter.h"
#include "Animation/AnimMontage.h"
#include "STUEquipFinishedAnimNotify.h"
#include "STUReloadingFinishedAnimNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "STUAnimUtils.h"

static constexpr int32 MaxWeapons = 2;

// Sets default values for this component's properties
USTUWeaponComponent::USTUWeaponComponent() :
	CurrentWeapon{nullptr},
	CurrentReloadAnimMontage{nullptr},
	CurrentWeaponIndex{0},
	bEquipAnimInProgress{false},
	bReloadingAnimInProgress{false}
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

void USTUWeaponComponent::Fire()
{
	if (CanFire()) CurrentWeapon->Fire();
}

void USTUWeaponComponent::StopFiring()
{
	if (CanFire()) CurrentWeapon->StopFiring();
}

void USTUWeaponComponent::NextWeapon()
{
	if (CanEquip())
	{
		CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
		EquipWeapon(CurrentWeaponIndex);
	}
}

void USTUWeaponComponent::Reload()
{
	if (!CanReload()) return;

	StopFiring();
	CurrentWeapon->Reload();
	bReloadingAnimInProgress = true;
	PlayAnimMontage(CurrentReloadAnimMontage);
}

FORCEINLINE bool USTUWeaponComponent::IsFiring() const
{
	return CurrentWeapon && CurrentWeapon->IsFiring();
}

FORCEINLINE bool USTUWeaponComponent::GetCurrentWeaponUIData(FWeaponUIData& UIData) const
{
	if (CurrentWeapon)
	{
		UIData = CurrentWeapon->GetUIData();
		return true;
	}
	return false;
}

bool USTUWeaponComponent::GetCurrentWeaponAmmo(FAmmoData& AmmoData) const
{
	if (CurrentWeapon)
	{
		AmmoData = CurrentWeapon->GetCurrentAmmo();
		return true;
	}
	return false;
}

// Called when the game starts
void USTUWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponData.Num() == MaxWeapons);

	InitAnimations();
	SpawnWeapons();
	EquipWeapon(CurrentWeaponIndex);
}

void USTUWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CurrentWeapon = nullptr;
	CurrentWeaponIndex = 0;
	for (auto Weapon : Weapons)
	{
		Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Weapon->Destroy();
	}
	Weapons.Empty();

	Super::EndPlay(EndPlayReason);
}

void USTUWeaponComponent::SpawnWeapons()
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	check(Character);

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = Character;

	for (const auto& Data : WeaponData)
	{
		ASTUWeapon* Weapon = GetWorld()->SpawnActor<ASTUWeapon>(Data.WeaponClass, SpawnParameters);
		if (!Weapon) continue;

		Weapon->OnClipEmpty.AddUObject(this, &USTUWeaponComponent::Reload);
		Weapons.Add(Weapon);
		AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocket);
	}
}

void USTUWeaponComponent::AttachWeaponToSocket(ASTUWeapon *const Weapon, USceneComponent *const Parent, const FName& SocketName)
{
	if (!Weapon || !Parent) return;

	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(Parent, AttachmentRules, SocketName);
}

void USTUWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
	check(WeaponIndex >= 0 && WeaponIndex < Weapons.Num());

	bEquipAnimInProgress = true;
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	check(Character);

	if (CurrentWeapon)
	{
		CurrentWeapon->StopFiring();
		AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocket);
	}

	CurrentWeapon = Weapons[WeaponIndex];
	AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocket);
	
	//CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
	const auto CurrentWeaponData = WeaponData.FindByPredicate(
		[Class = this->CurrentWeapon->GetClass()](const FWeaponData& Data) { return Data.WeaponClass == Class; });
	CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;
	
	PlayAnimMontage(EquipAnimMontage);
}

void USTUWeaponComponent::PlayAnimMontage(UAnimMontage* const AnimMontage) const
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	check(Character);
	
	Character->PlayAnimMontage(AnimMontage);
}

void USTUWeaponComponent::InitAnimations()
{
	auto EquipFinishedNotify = STUAnimUtils::FindAnimNotifyByClass<USTUEquipFinishedAnimNotify>(EquipAnimMontage);
	check(EquipFinishedNotify);
	EquipFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnEquipFinished);

	for (const auto& Data : WeaponData)
	{
		auto ReloadingFinishedNotify = STUAnimUtils::FindAnimNotifyByClass<USTUReloadingFinishedAnimNotify>(Data.ReloadAnimMontage);
		check(ReloadingFinishedNotify);
		ReloadingFinishedNotify->OnNotified.AddUObject(this, &USTUWeaponComponent::OnReloadingFinished);
	}
}

void USTUWeaponComponent::OnEquipFinished(const USkeletalMeshComponent *const MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	
	if (Character && Character->GetMesh() == MeshComp)
	{
		bEquipAnimInProgress = false;
	}
}

void USTUWeaponComponent::OnReloadingFinished(const USkeletalMeshComponent* const MeshComp)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());

	if (Character && Character->GetMesh() == MeshComp)
	{
		bReloadingAnimInProgress = false;
	}
}

FORCEINLINE bool USTUWeaponComponent::CanReload() const
{
	return CanFire() && CurrentWeapon->CanReload();
}

