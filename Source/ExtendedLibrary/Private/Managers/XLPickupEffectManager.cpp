// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Managers/XLPickupEffectManager.h"

UXLPickupEffectManager::UXLPickupEffectManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLPickupEffectManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLPickupEffectManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



