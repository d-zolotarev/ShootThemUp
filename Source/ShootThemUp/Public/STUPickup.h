// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUPickup.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUPickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual bool GivePickupTo(APawn *const PlayerPawn);

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Collision")
	class USphereComponent* SphereComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Mesh")
	class UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Respawn")
	float RespawnTime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

private:
	void PickupWasTaken();
	void Respawn();
	void SetVisibility(bool bIsVisible);
};
