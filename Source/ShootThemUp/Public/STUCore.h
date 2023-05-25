#pragma once

#include "CoreMinimal.h"
#include "STUCore.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmptySignature, class ASTUWeapon*);
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, const class USkeletalMeshComponent* const);

USTRUCT(BlueprintType)
struct FAmmoData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (ClampMin = "0"))
	int32 Bullets;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo", meta = (ClampMin = "0", EditCondition = "!Infinite"))
	int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
	bool Infinite;

	friend FORCEINLINE bool operator==(const FAmmoData& l, const FAmmoData& r)
	{
		return l.Bullets == r.Bullets && l.Clips == r.Clips;
	}

};

USTRUCT(BlueprintType)
struct FWeaponUIData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	class UTexture2D* MainIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	class UTexture2D* CrosshairIcon;
};

USTRUCT(BlueprintType)
struct FWeaponData
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	TSubclassOf<class ASTUWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	class UAnimMontage* ReloadAnimMontage;
};
