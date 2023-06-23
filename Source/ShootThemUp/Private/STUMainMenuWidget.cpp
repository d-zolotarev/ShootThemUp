// Fill out your copyright notice in the Description page of Project Settings.


#include "STUMainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

void USTUMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
		StartGameButton->OnClicked.AddDynamic(this, &USTUMainMenuWidget::OnStartGame);

	if (QuitGameButton)
		QuitGameButton->OnClicked.AddDynamic(this, &USTUMainMenuWidget::OnQuitGame);
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

void USTUMainMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}
