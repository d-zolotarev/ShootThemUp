// Fill out your copyright notice in the Description page of Project Settings.


#include "STUHealthBarWidget.h"
#include "Components/ProgressBar.h"

USTUHealthBarWidget::USTUHealthBarWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetHealthPercent(1.f);
}

FORCEINLINE void USTUHealthBarWidget::SetHealthPercent(float HealthPercent)
{
	SetVisibility((HealthPercent > PercentVisibilityThreshold || FMath::IsNearlyZero(HealthPercent)) ?
		ESlateVisibility::Hidden : ESlateVisibility::Visible);

	if (HealthBar)
	{
		HealthBar->SetFillColorAndOpacity((HealthPercent > PercentColorThreshold) ? GoodColor : BadColor);
		HealthBar->SetPercent(HealthPercent);
	}
}
