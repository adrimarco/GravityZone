// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AmmoCounterWidget.generated.h"

class ULabel;
class UWeaponComponent;

UCLASS()
class GRAVITYZONE_API UAmmoCounterWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	ULabel* LoadedAmmoLabel{ nullptr };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets", meta = (BindWidget))
	ULabel* ReserveAmmoLabel{ nullptr };

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UWeaponComponent* Weapon{ nullptr };

public:
	UFUNCTION(BlueprintCallable)
	void SetLoadedAmmo(int32 Ammo);

	UFUNCTION(BlueprintCallable)
	void SetReserveAmmo(int32 Ammo);

	UFUNCTION(BlueprintCallable)
	void SetWeaponReference(UWeaponComponent* NewWeapon);
};
