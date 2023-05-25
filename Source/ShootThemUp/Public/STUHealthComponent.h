// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STUCore.h"
#include "STUHealthComponent.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SHOOTTHEMUP_API USTUHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTUHealthComponent();

	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetHealth() const { return Health; }
	
	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE float GetHealthPercent() const { return Health / MaxHealth; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	FORCEINLINE bool IsDead() const { return FMath::IsNearlyZero(Health); }

public:
	bool TryToAddHealth(int32 HealthAmount);

public:
	FOnDeathSignature OnDeath;
	FOnHealthChanged OnHealthChanged;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health", meta = (ClampMin = "0.1", ClampMax = "100.0"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health | AutoHeal")
	bool bAutoHealEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health | AutoHeal", meta = (EditCondition = "bAutoHealEnabled"))
	float AutoHealDelay;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health | AutoHeal", meta = (EditCondition = "bAutoHealEnabled"))
	float HealthUpdateRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health | AutoHeal", meta = (EditCondition = "bAutoHealEnabled"))
	float HealModifier;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

private:
	void AutoHeal();
	void SetHealth(float Value);
	FORCEINLINE bool IsHealthFull() const { return FMath::IsNearlyEqual(Health, MaxHealth); }

private:
	float Health;
	FTimerHandle AutoHealTimerHandle;
};
