// Fill out your copyright notice in the Description page of Project Settings.


#include "STUMainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "STUGameInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "STUMapItemWidget.h"

void USTUMainMenuWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (StartGameButton)
		StartGameButton->OnClicked.AddDynamic(this, &USTUMainMenuWidget::OnStartGame);

	if (QuitGameButton)
		QuitGameButton->OnClicked.AddDynamic(this, &USTUMainMenuWidget::OnQuitGame);

	InitMapItems();
}

FORCEINLINE void USTUMainMenuWidget::OnStartGame()
{
	if (const USTUGameInstance* const GameInstance = GetGameInstance())
	{
		UGameplayStatics::OpenLevel(GetWorld(), GameInstance->GetStartupLevel().MapName);
	}
}

FORCEINLINE void USTUMainMenuWidget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, true);
}

void USTUMainMenuWidget::InitMapItems()
{
	if (const USTUGameInstance* const GameInstance = GetGameInstance())
	{
		checkf(GameInstance->GetMapsData().Num() > 0, TEXT("Levels is not set"));
		
		if (MapsHorizontalBox)
		{
			MapsHorizontalBox->ClearChildren();

			for (const auto& MapData : GameInstance->GetMapsData())
			{
				if (USTUMapItemWidget* const MapItemWidget = CreateWidget<USTUMapItemWidget>(this, MapItemWidgetClass))
				{
					MapItemWidget->SetMapData(MapData);
					MapItemWidget->OnMapSelected.AddUObject(this, &USTUMainMenuWidget::OnMapSelected);
					MapsHorizontalBox->AddChild(MapItemWidget);
					MapItemWidgets.Add(MapItemWidget);
				}
			}
		}

		OnMapSelected(GameInstance->GetStartupLevel().MapName.IsNone() ? MapItemWidgets[0]->GetMapData() : GameInstance->GetStartupLevel());
	}
}

void USTUMainMenuWidget::OnMapSelected(const FMapData& SelectedMapData)
{
	if (USTUGameInstance* const GameInstance = GetGameInstance())
	{
		GameInstance->SetStartupLevel(SelectedMapData);

		for (USTUMapItemWidget* const MapItemWidget : MapItemWidgets)
		{
			if (MapItemWidget)
			{
				MapItemWidget->SetSelected(SelectedMapData.MapName == MapItemWidget->GetMapData().MapName);
			}
		}
	}
}

FORCEINLINE USTUGameInstance* USTUMainMenuWidget::GetGameInstance() const
{
	return GetWorld() ? GetWorld()->GetGameInstance<USTUGameInstance>() : nullptr;
}
