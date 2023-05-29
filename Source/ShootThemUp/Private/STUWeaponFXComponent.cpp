// Fill out your copyright notice in the Description page of Project Settings.


#include "STUWeaponFXComponent.h"
//#include "NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
USTUWeaponFXComponent::USTUWeaponFXComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USTUWeaponFXComponent::BeginPlay()
{
	Super::BeginPlay();
}

void USTUWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
	auto ImpactData = DefaultImpactData;

	if (const auto PhysMaterial = HitResult.PhysMaterial; PhysMaterial.IsValid())
	{
		if (const auto PhysMaterialRaw = PhysMaterial.Get(); ImpactDataMap.Contains(PhysMaterialRaw))
		{
			ImpactData = ImpactDataMap[PhysMaterialRaw];
		}
	}

	/*
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactData.NiagaraEffect,
		HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
		*/

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactData.ImpactEffect, HitResult.ImpactPoint, HitResult.ImpactPoint.Rotation());

	auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), ImpactData.DecalData.Material, ImpactData.DecalData.Size,
		HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
	if (DecalComponent)
	{
		DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
	}
}

