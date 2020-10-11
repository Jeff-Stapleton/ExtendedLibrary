// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Managers/XLPlayerEffectManager.h"

UXLPlayerEffectManager::UXLPlayerEffectManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLPlayerEffectManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLPlayerEffectManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



