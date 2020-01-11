// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLVehicleRangedWeapon.h"

AXLVehicleRangedWeapon::AXLVehicleRangedWeapon()
{

}


void AXLVehicleRangedWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AXLVehicleRangedWeapon::Destroyed()
{
	Super::Destroyed();

	StopFX();
}
