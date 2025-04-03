// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthDisplayWidget.h"
#include "Label.h"
#include "Components/ProgressBar.h"

void UHealthDisplayWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (HealthBar && NumericLabel) {
		SetHealth(100, 100);
	}
}

void UHealthDisplayWidget::SetHealth(float CurrentHealth, float MaxHealth)
{
	verify(NumericLabel && HealthBar);
	int32 DisplayedHealthNumber{ FMath::Max(FMath::RoundToInt(CurrentHealth), 0) };
	float HealthPercent{ CurrentHealth / MaxHealth };

	NumericLabel->SetText(FText::AsNumber(DisplayedHealthNumber));
	HealthBar->SetPercent(HealthPercent);
}
