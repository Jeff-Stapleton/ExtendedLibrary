// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeaponCan.h"

bool XLWeaponCan::Attack(AXLWeapon* Weapon)
{
	/*if (Weapon->AttackSpeed <= 0.0f && Weapon->WeaponState->GetWeaponState() != EWeaponState::Reloading && Weapon->WeaponState->GetWeaponState() != EWeaponState::Meleeing)
	{
		return true;
	}
	else
	{
		return false;
	}*/
	return true;
}

bool XLWeaponCan::Reload(AXLWeapon* Weapon)
{
	return true;
}

bool XLWeaponCan::Melee(AXLWeapon* Weapon)
{
	return true;
}

