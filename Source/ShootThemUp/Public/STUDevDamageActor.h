// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STUDevDamageActor.generated.h"

UCLASS()
class SHOOTTHEMUP_API ASTUDevDamageActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASTUDevDamageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class USceneComponent* SceneComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSphere")
	float Radius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSphere")
	FColor Color;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSphere")
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DamageSphere")
	bool bDoFullDamage;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
