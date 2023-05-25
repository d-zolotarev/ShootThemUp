// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPickup.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASTUPickup::ASTUPickup() : RespawnTime{30.f}, Yaw{10.f}
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
	check(SphereComponent);
	SphereComponent->InitSphereRadius(50.f);
	SphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	SetRootComponent(SphereComponent);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("StaticMesh");
	check(StaticMesh);
	StaticMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ASTUPickup::BeginPlay()
{
	Super::BeginPlay();
	
	GenerateYaw();
}

bool ASTUPickup::GivePickupTo(APawn *const PlayerPawn)
{
	return false;
}

// Called every frame
void ASTUPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AddActorWorldRotation(FRotator(0.f, Yaw, 0.f));
}

void ASTUPickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const auto PlayerPawn = Cast<APawn>(OtherActor);
	if (GivePickupTo(PlayerPawn))
		PickupWasTaken();
}

void ASTUPickup::PickupWasTaken()
{
	SetVisibility(false);

	FTimerHandle RespawnTimerHandle;
	GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &ASTUPickup::Respawn, RespawnTime);
}

FORCEINLINE void ASTUPickup::Respawn()
{
	GenerateYaw();
	SetVisibility(true);
}

FORCEINLINE void ASTUPickup::SetVisibility(bool bIsVisible)
{
	SphereComponent->SetCollisionResponseToAllChannels(bIsVisible ? ECollisionResponse::ECR_Overlap : ECollisionResponse::ECR_Ignore);
	GetRootComponent()->SetVisibility(bIsVisible, true);
}

FORCEINLINE void ASTUPickup::GenerateYaw()
{
	const float Direction = FMath::RandBool() ? 1.f : -1.f;
	Yaw = FMath::RandRange(1.f, 2.f) * Direction;
}

