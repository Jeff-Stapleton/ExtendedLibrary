// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeaponSoundManager.h"

UXLWeaponSoundManager::UXLWeaponSoundManager()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLWeaponSoundManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLWeaponSoundManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



