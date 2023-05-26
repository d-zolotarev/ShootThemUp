// Fill out your copyright notice in the Description page of Project Settings.


#include "STUCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "STUCharacterMovementComponent.h"
#include "STUHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Animation/AnimMontage.h"
#include "GameFramework/Controller.h"
#include "STUWeaponComponent.h"

// Sets default values
ASTUCharacter::ASTUCharacter(const FObjectInitializer& ObjectInitializer) :
	Super(ObjectInitializer.SetDefaultSubobjectClass<USTUCharacterMovementComponent>(ASTUCharacter::CharacterMovementComponentName)),
	LandedDamageVelocity(600.f, 1000.f),
	LandedDamage(10.f, 100.f),
	bWantsToRun{false},
	bIsMovingForward{false}
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	bUseControllerRotationPitch = bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = true;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;

	HealthComponent = CreateDefaultSubobject<USTUHealthComponent>("HealthComponent");
	check(HealthComponent);
	
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthTextComponent");
	check(HealthTextComponent);
	HealthTextComponent->SetupAttachment(GetRootComponent());
	HealthTextComponent->HorizontalAlignment = EHorizTextAligment::EHTA_Center;
	HealthTextComponent->VerticalAlignment = EVerticalTextAligment::EVRTA_TextCenter;
	HealthTextComponent->SetOwnerNoSee(true);

	WeaponComponent = CreateDefaultSubobject<USTUWeaponComponent>("WeaponComponent");
	check(WeaponComponent);
}

// Called when the game starts or when spawned
void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnHealthChanged(HealthComponent->GetHealth(), 0.f);

	HealthComponent->OnDeath.AddUObject(this, &ASTUCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ASTUCharacter::OnHealthChanged);
}

void ASTUCharacter::OnDeath()
{
	WeaponComponent->StopFiring();

	if (Controller)
	{
		Controller->ChangeState(NAME_Spectating);
	}

	//PlayAnimMontage(DeathAnimation);
	SetLifeSpan(5.f);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldDynamic, ECollisionResponse::ECR_Ignore);
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);
}

void ASTUCharacter::Fire()
{
	if (IsRunning()) return;
	
	WeaponComponent->Fire();
}

void ASTUCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		bIsMovingForward = Value > 0.f;
		AddMovementInput(GetActorForwardVector(), Value);
	}

	if (IsRunning() && WeaponComponent->IsFiring()) WeaponComponent->StopFiring();
}

void ASTUCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ASTUCharacter::Run()
{
	bWantsToRun = true;
	if (IsRunning()) WeaponComponent->StopFiring();
}

// Called every frame
void ASTUCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASTUCharacter::OnHealthChanged(float Value, float Delta)
{
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Value)));
}

// Called to bind functionality to input
void ASTUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASTUCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASTUCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ASTUCharacter::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ASTUCharacter::StopRunning);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASTUCharacter::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &USTUWeaponComponent::StopFiring);

	PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &USTUWeaponComponent::NextWeapon);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &USTUWeaponComponent::ReloadCurrentWeapon);
}

void ASTUCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);

	const float FallVelocityZ = FMath::Abs(GetVelocity().Z);
	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const float Damage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(Damage, FDamageEvent(), nullptr, nullptr);
}

