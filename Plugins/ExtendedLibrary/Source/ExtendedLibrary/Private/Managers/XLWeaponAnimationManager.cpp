// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeaponAnimationManager.h"

UXLWeaponAnimationManager::UXLWeaponAnimationManager()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLWeaponAnimationManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLWeaponAnimationManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



