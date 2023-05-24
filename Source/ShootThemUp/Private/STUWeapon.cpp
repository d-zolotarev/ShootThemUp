// Fill out your copyright notice in the Description page of Project Settings.


#include "STUWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "STUCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values
ASTUWeapon::ASTUWeapon() : TraceMaxDistance{10'000.f}, ScatterAngle{3.f}, bIsFiring{false}
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMesh = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMesh");
	check(SkeletalMesh);
	SetRootComponent(SkeletalMesh);
}

void ASTUWeapon::Fire()
{
	bIsFiring = true;
	MakeShot();
}

void ASTUWeapon::StopFiring()
{
	bIsFiring = false;
}

// Called when the game starts or when spawned
void ASTUWeapon::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmo = DefaultAmmo;
}

void ASTUWeapon::MakeShot()
{
}

FHitResult ASTUWeapon::Hit() const
{
	FQuat MuzzleSocketRotation;
	FVector MuzzleSocketLocation;
	GetMuzzleSocketPosition(MuzzleSocketRotation, MuzzleSocketLocation);

	// �� �������� ���� � ����.
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(GetOwner());

	FVector TraceStart, TraceEnd;
	GetTraceFromCamera(TraceStart, TraceEnd);

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, CollisionQueryParams);

	const FVector MuzzleSocketForwardVector = MuzzleSocketRotation.GetForwardVector();
	// ���� ����� ��������� �������� � ����������� ����.
	float Angle = FMath::Acos(FVector::DotProduct(MuzzleSocketForwardVector.GetSafeNormal(),
		(HitTraceEnd(HitResult) - MuzzleSocketLocation).GetSafeNormal()));

	// ���� ���� ������ pi/2, ������ �������� ���� �� �����.
	if (Angle > HALF_PI)
	{
		TraceEnd = MuzzleSocketLocation + Scatter(MuzzleSocketForwardVector) * TraceMaxDistance;
		GetWorld()->LineTraceSingleByChannel(HitResult, MuzzleSocketLocation, TraceEnd, ECC_Visibility, CollisionQueryParams);
	}

	HitResult.TraceStart = MuzzleSocketLocation;

	return HitResult;
}

FORCEINLINE FVector ASTUWeapon::Scatter(const FVector& Direction) const
{
	return FMath::VRandCone(Direction, FMath::DegreesToRadians(ScatterAngle * .5f));
}

FORCEINLINE APlayerController* ASTUWeapon::GetPlayerController() const
{
	const auto OwningCharacter = Cast<ACharacter>(GetOwner());
	if (!OwningCharacter) return nullptr;

	return OwningCharacter->GetController<APlayerController>();
}

FORCEINLINE void ASTUWeapon::GetPlayerViewPoint(FVector& Location, FRotator& Rotation) const
{
	const auto Controller = GetPlayerController();
	check(Controller);

	Controller->GetPlayerViewPoint(Location, Rotation);
}

FORCEINLINE void ASTUWeapon::GetMuzzleSocketPosition(FQuat& Rotation, FVector& Location) const
{
	const FTransform MuzzleSocketTransform = SkeletalMesh->GetSocketTransform(MuzzleSocketName);
	
	Rotation = MuzzleSocketTransform.GetRotation();
	Location = MuzzleSocketTransform.GetLocation();
}

FORCEINLINE void ASTUWeapon::GetTraceFromCamera(FVector& TraceStart, FVector& TraceEnd) const
{
	FRotator CameraRotation;
	GetPlayerViewPoint(TraceStart, CameraRotation);
	TraceEnd = TraceStart + Scatter(CameraRotation.Vector()) * TraceMaxDistance;
}

FORCEINLINE FVector ASTUWeapon::HitTraceEnd(const FHitResult& HitResult) const
{
	return FVector(HitResult.bBlockingHit ? HitResult.ImpactPoint : HitResult.TraceEnd);
}

FORCEINLINE void ASTUWeapon::DecreaseAmmo()
{
	CurrentAmmo.Bullets--;

	LogAmmo();

	if (IsClipEmpty() && !IsAmmoEmpty())
	{
		StopFiring();
		OnClipEmpty.Broadcast();
	}
}

FORCEINLINE void ASTUWeapon::Reload()
{
	if (IsAmmoEmpty()) return;
	
	CurrentAmmo.Clips--;
	CurrentAmmo.Bullets = DefaultAmmo.Bullets;

	UE_LOG(LogTemp, Warning, TEXT("Realoaded"));
	LogAmmo();
}

FORCEINLINE void ASTUWeapon::LogAmmo() const
{
	if (CurrentAmmo.Infinite)
	{
		UE_LOG(LogTemp, Warning, TEXT("Ammo: INFINITE"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Ammo: %d/%d"), CurrentAmmo.Bullets, CurrentAmmo.Clips);
	}
}

