// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "STUCharacterMovementComponent.h"
#include "STUWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"


ASTUPlayerCharacter::ASTUPlayerCharacter(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	check(CameraBoom);
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 300.f;
	CameraBoom->bUsePawnControlRotation = true;
	CameraBoom->SocketOffset = FVector(0.f, 100.f, 80.f);

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	check(Camera);
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	check(CameraCollisionComponent);
	CameraCollisionComponent->SetupAttachment(Camera);
	CameraCollisionComponent->SetSphereRadius(10.f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	bUseControllerRotationPitch = bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;

	GetCharacterMovement()->bOrientRotationToMovement = false;
}

// Called to bind functionality to input
void ASTUPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUPlayerCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUPlayerCharacter::StopRunning);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASTUPlayerCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFiring);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::ReloadCurrentWeapon);
}

void ASTUPlayerCharacter::OnDeath()
{
	Super::OnDeath();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}
}

void ASTUPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASTUPlayerCharacter::OnCameraCollisionEndOverlap);
}

FORCEINLINE void ASTUPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}

FORCEINLINE void ASTUPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}

void ASTUPlayerCharacter::Fire()
{
	if (IsRunning()) return;

	WeaponComponent->Fire();
}

void ASTUPlayerCharacter::CheckCameraOverlap()
{
	const bool HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);

	TArray<USceneComponent*> ChildrenMeshes;
	GetMesh()->GetChildrenComponents(true, ChildrenMeshes);

	for (USceneComponent* const ChildMesh : ChildrenMeshes)
	{
		if (UPrimitiveComponent* const Comp = Cast<UPrimitiveComponent>(ChildMesh))
			Comp->SetOwnerNoSee(HideMesh);
	}
}

void ASTUPlayerCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		bIsMovingForward = Value > 0.f;
		AddMovementInput(GetActorForwardVector(), Value);
	}

	if (IsRunning() && WeaponComponent->IsFiring()) WeaponComponent->StopFiring();
}

void ASTUPlayerCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ASTUPlayerCharacter::Run()
{
	bWantsToRun = true;
	if (IsRunning()) WeaponComponent->StopFiring();
}


