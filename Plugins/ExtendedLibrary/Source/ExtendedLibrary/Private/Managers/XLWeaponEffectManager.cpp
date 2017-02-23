// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeaponEffectManager.h"

UXLWeaponEffectManager::UXLWeaponEffectManager()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLWeaponEffectManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLWeaponEffectManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



