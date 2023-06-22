// Fill out your copyright notice in the Description page of Project Settings.


#include "ReturnToMainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"

void UReturnToMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (ReturnToMainMenuButton)
		ReturnToMainMenuButton->OnClicked.AddDynamic(this, &UReturnToMainMenuWidget::OnReturnToMainMenu);
}

void UReturnToMainMenuWidget::OnReturnToMainMenu()
{
	if (!GetWorld()) return;

	if (const USTUGameInstance* const GameInstance = GetWorld()->GetGameInstance<USTUGameInstance>();
		GameInstance && !GameInstance->GetMainMenuLevelName().IsNone())
	{
		UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetMainMenuLevelName());
	}
}
