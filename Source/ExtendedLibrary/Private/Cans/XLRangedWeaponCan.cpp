// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLRangedWeaponCan.h"

bool XLRangedWeaponCan::Fire(AXLRangedWeapon* Weapon)
{
	return Weapon->WeaponState != EWeaponState::OutOfAmmo;
}
