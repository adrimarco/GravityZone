// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HealthDisplayWidget.generated.h"

class ULabel;
class UProgressBar;

UCLASS()
class GRAVITYZONE_API UHealthDisplayWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	ULabel* NumericLabel{ nullptr };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UProgressBar* HealthBar{ nullptr };

protected:
	virtual void NativePreConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetHealth(float CurrentHealth, float MaxHealth);
};
