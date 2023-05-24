// Fill out your copyright notice in the Description page of Project Settings.


#include "STUCharacterMovementComponent.h"
#include "STUCharacter.h"

float USTUCharacterMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();

	const ASTUCharacter* Character = Cast<ASTUCharacter>(GetPawnOwner());

	return Character && Character->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
