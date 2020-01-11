// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLVehicleWeaponManager.h"

UXLVehicleWeaponManager::UXLVehicleWeaponManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLVehicleWeaponManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLVehicleWeaponManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}



