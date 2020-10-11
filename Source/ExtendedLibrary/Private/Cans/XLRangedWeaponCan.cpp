// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Cans/XLRangedWeaponCan.h"

bool XLRangedWeaponCan::Fire(AXLItem* Weapon)
{
	return Weapon->PrimaryState != EItemPrimaryState::OutOfAmmo;
}
