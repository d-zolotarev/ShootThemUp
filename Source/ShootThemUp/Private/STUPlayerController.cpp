// Fill out your copyright notice in the Description page of Project Settings.


#include "STUPlayerController.h"
#include "STURespawnComponent.h"

ASTUPlayerController::ASTUPlayerController()
{
	RespawnComponent = CreateDefaultSubobject<USTURespawnComponent>("RespawnComponent");
	check(RespawnComponent);
}
