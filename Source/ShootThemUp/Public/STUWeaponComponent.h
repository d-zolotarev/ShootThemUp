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

	virtual void Fire();
	void StopFiring();
	virtual void NextWeapon();
	void Reload(class ASTUWeapon* Weapon);
	bool IsFiring() const;
	bool GetCurrentWeaponUIData(FWeaponUIData& UIData) const;
	bool GetCurrentWeaponAmmo(FAmmoData& AmmoData) const;
	bool TryToAddAmmo(int32 ClipsAmount, TSubclassOf<class ASTUWeapon> WeaponClass);
	void ReloadCurrentWeapon();

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
	FORCEINLINE bool CanFire() const { return CurrentWeapon && CanEquip(); }
	FORCEINLINE bool CanEquip() const { return !bEquipAnimInProgress && !bReloadingAnimInProgress; }
	void EquipWeapon(int32 WeaponIndex);

protected:
	UPROPERTY()
	ASTUWeapon* CurrentWeapon;

	UPROPERTY()
	TArray<ASTUWeapon*> Weapons;

	int32 CurrentWeaponIndex;

private:
	void SpawnWeapons();
	void AttachWeaponToSocket(ASTUWeapon *const Weapon, USceneComponent *const Parent, const FName& SocketName);
	void PlayAnimMontage(UAnimMontage *const AnimMontage) const;
	void InitAnimations();
	void OnEquipFinished(const USkeletalMeshComponent *const MeshComp);
	void OnReloadingFinished(const USkeletalMeshComponent* const MeshComp);
	bool CanReload() const;
	
private:
	UPROPERTY()
	UAnimMontage* CurrentReloadAnimMontage;

	bool bEquipAnimInProgress;
	bool bReloadingAnimInProgress;
};
