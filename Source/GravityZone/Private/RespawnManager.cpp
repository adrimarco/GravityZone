// Fill out your copyright notice in the Description page of Project Settings.


#include "RespawnManager.h"
#include "Respawnable.h"

void IRespawnManager::EnableRespawn(bool bNewActiveState)
{
	if (bNewActiveState)
		URespawnable::OnRespawnRequested.BindRaw(this, &IRespawnManager::RespawnPlayer);
	else
		URespawnable::OnRespawnRequested.Unbind();
}

