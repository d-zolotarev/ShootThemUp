// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthComponent.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"
#include "Camera/CameraShakeBase.h"
#include "STUUtils.h"
#include "../ShootThemUpGameModeBase.h"

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

	const APawn* const Pawn = Cast<APawn>(GetOwner());
	AController* const Controller = Pawn ? Pawn->GetController() : nullptr;

	if (Damage <= 0.f || IsDead() || !STUUtils::AreEnemies(InstigatedBy, Controller)) return;
	
	SetHealth(Health - Damage);

	if (IsDead())
	{
		if (AShootThemUpGameModeBase* const GameMode = Cast<AShootThemUpGameModeBase>(GetWorld()->GetAuthGameMode()))
		{
			GameMode->Killed(InstigatedBy, Controller);
		}

		OnDeath.Broadcast();
	}
	else if (bAutoHealEnabled)
	{
		GetWorld()->GetTimerManager().SetTimer(AutoHealTimerHandle, this, &USTUHealthComponent::AutoHeal, HealthUpdateRate, true, AutoHealDelay);
	}

	PlayCameraShake();
}

FORCEINLINE void USTUHealthComponent::SetHealth(float Value)
{
	float OldHealth = Health;
	Health = FMath::Clamp(Value, 0.f, MaxHealth);
	if (!FMath::IsNearlyEqual(OldHealth, Health))
		OnHealthChanged.Broadcast(Health, Health - OldHealth);
}

void USTUHealthComponent::PlayCameraShake()
{
	if (IsDead()) return;

	const APawn* const Pawn = Cast<APawn>(GetOwner());
	if (!Pawn) return;

	const APlayerController* const Controller = Pawn->GetController<APlayerController>();
	if (!Controller || !Controller->PlayerCameraManager) return;

	Controller->PlayerCameraManager->StartCameraShake(CameraShake);
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
