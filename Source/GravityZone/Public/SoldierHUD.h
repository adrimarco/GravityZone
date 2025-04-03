// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SoldierHUD.generated.h"

class UHealthDisplayWidget;
class UAmmoCounterWidget;
class UGravityChargesContainer;
class UImage;
class ASoldierCharacter;

UCLASS()
class GRAVITYZONE_API USoldierHUD : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UHealthDisplayWidget* HealthDisplay{ nullptr };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UAmmoCounterWidget* AmmoCounter{ nullptr };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UGravityChargesContainer* GravityChargesDisplay{ nullptr };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	UImage* Crosshair{ nullptr };

public:
	UFUNCTION(BlueprintCallable)
	void BindToSoldierCharacter(ASoldierCharacter* Character);
};
