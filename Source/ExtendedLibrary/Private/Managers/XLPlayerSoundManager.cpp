// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Managers/XLPlayerSoundManager.h"

UXLPlayerSoundManager::UXLPlayerSoundManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLPlayerSoundManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLPlayerSoundManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



