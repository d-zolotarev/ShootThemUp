// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCore.h"
#include "STUWeaponComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUWeaponComponent();

	void Fire();
	void StopFiring();
	void NextWeapon();
	void Reload();
	bool IsFiring() const;
	bool GetWeaponUIData(FWeaponUIData& UIData) const;
	bool GetWeaponAmmo(FAmmoData& AmmoData) const;

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TArray<FWeaponData> WeaponData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponEquipSocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName WeaponArmorySocket;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation")
	UAnimMontage* EquipAnimMontage;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

private:
	void SpawnWeapons();
	void AttachWeaponToSocket(ASTUWeapon *const Weapon, USceneComponent *const Parent, const FName& SocketName);
	void EquipWeapon(int32 WeaponIndex);
	void PlayAnimMontage(UAnimMontage *const AnimMontage) const;
	void InitAnimations();
	void OnEquipFinished(const USkeletalMeshComponent *const MeshComp);
	void OnReloadingFinished(const USkeletalMeshComponent* const MeshComp);
	FORCEINLINE bool CanFire() const { return CurrentWeapon && CanEquip(); }
	FORCEINLINE bool CanEquip() const { return !bEquipAnimInProgress && !bReloadingAnimInProgress; }
	bool CanReload() const;
	
private:
	UPROPERTY()
	ASTUWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<ASTUWeapon*> Weapons;

	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage;

	int32 CurrentWeaponIndex;
	bool bEquipAnimInProgress;
	bool bReloadingAnimInProgress;
};
