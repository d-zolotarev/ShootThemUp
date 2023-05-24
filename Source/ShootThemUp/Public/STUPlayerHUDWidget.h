// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STUCore.h"
#include "STUPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTTHEMUP_API USTUPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetHealthPercent() const;

	UFUNCTION(BlueprintCallable, Category = "Weapon")
	bool GetWeaponUIData(FWeaponUIData& UIData) const;

private:
	template<typename T>
	T* GetComponentByClass(TSubclassOf<UActorComponent> ComponentClass) const;
};

template<typename T>
FORCEINLINE T* USTUPlayerHUDWidget::GetComponentByClass(TSubclassOf<UActorComponent> ComponentClass) const
{
	const auto OwningPlayer = GetOwningPlayerPawn();
	if (!OwningPlayer) return nullptr;

	return Cast<T>(OwningPlayer->GetComponentByClass(ComponentClass));
}
