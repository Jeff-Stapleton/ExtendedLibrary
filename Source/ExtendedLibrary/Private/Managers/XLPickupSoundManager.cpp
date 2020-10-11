// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Managers/XLPickupSoundManager.h"

UXLPickupSoundManager::UXLPickupSoundManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLPickupSoundManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLPickupSoundManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



