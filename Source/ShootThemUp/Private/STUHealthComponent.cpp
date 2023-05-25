// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

// Sets default values for this component's properties
USTUHealthComponent::USTUHealthComponent() :
	MaxHealth{100.f},
	bAutoHealEnabled{true},
	AutoHealDelay{3.f},
	HealthUpdateRate{1.f},
	HealModifier{5.f},
	Health{0.f}
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

bool USTUHealthComponent::TryToAddHealth(int32 HealthAmount)
{
	if (IsDead() || IsHealthFull())
		return false;

	SetHealth(Health + HealthAmount);
	return true;
}

// Called when the game starts
void USTUHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	SetHealth(MaxHealth);

	if (AActor* Owner = GetOwner())
	{
		Owner->OnTakeAnyDamage.AddDynamic(this, &USTUHealthComponent::OnTakeAnyDamage);
	}
}

void USTUHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser)
{
	GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);

	if (Damage <= 0.f || IsDead()) return;
	
	SetHealth(Health - Damage);

	if (IsDead())
	{
		OnDeath.Broadcast();
	}
	else if (bAutoHealEnabled)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoHealTimerHandle, this, &USTUHealthComponent::AutoHeal, HealthUpdateRate, true, AutoHealDelay);
	}
}

FORCEINLINE void USTUHealthComponent::SetHealth(float Value)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Value, 0.f, MaxHealth);
	if (!FMath::IsNearlyEqual(OldHealth, Health))
		OnHealthChanged.Broadcast(Health);
}

void USTUHealthComponent::AutoHeal()
{
	if (IsDead() || IsHealthFull())
	{
		GetWorld()->GetTimerManager().ClearTimer(AutoHealTimerHandle);

		return;
	}

	SetHealth(Health + HealModifier);
}
