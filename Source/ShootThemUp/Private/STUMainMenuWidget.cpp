// Fill out your copyright notice in the Description page of Project Settings.


#include "STUMainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

void USTUMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
		StartGameButton->OnClicked.AddDynamic(this, &USTUMainMenuWidget::OnStartGame);
}

void USTUMainMenuWidget::OnStartGame()
{
	if (!GetWorld()) return;

	if (const USTUGameInstance* const GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
		GameInstance && !GameInstance->GetStartupLevelName().IsNone())
	{
		UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetStartupLevelName());
	}
}
