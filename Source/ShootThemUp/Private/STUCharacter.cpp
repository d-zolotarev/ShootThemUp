// Fill out your copyright notice in the Description page of Project Settings.


#include "STUCharacter.h"
#include "STUCharacterMovementComponent.h"
#include "STUHealthComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Controller.h"
#include "STUWeaponComponent.h"

// Sets default values
ASTUCharacter::ASTUCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ASTUCharacter::CharacterMovementComponentName)),
	LandedDamageVelocity(600.f, 1000.f),
	LandedDamage(10.f, 100.f),
	MaterialColorParameter("Paint Color")
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
	check(HealthComponent);
	
	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
	check(WeaponComponent);
}

// Called when the game starts or when spawned
void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();

	HealthComponent->OnDeath.AddUObject(this, &ASTUCharacter::OnDeath);
}

void ASTUCharacter::OnDeath()
{
	WeaponComponent->StopFiring();

	SetLifeSpan(5.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}


// Called every frame
void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTUCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	const float FallVelocityZ = FMath::Abs(GetVelocity().Z);
	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const float Damage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);
}

FORCEINLINE void ASTUCharacter::SetPlayerColor(const FLinearColor& Color)
{
	if (UMaterialInstanceDynamic* const MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0))
	{
		MaterialInstance->SetVectorParameterValue(MaterialColorParameter, Color);
	}
}

