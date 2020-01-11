// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeaponManager.h"

UXLWeaponManager::UXLWeaponManager()
{
	bReplicates = true;
}

void UXLWeaponManager::DestroyInventory()
{
	/*if (Role < ROLE_Authority)
	{
		return;
	}*/

	// remove all weapons from inventory and destroy them
	for (int32 i = Inventory.Num() - 1; i >= 0; i--)
	{
		AXLWeapon* Weapon = Inventory[i];
		if (Weapon)
		{
			Inventory.RemoveSingle(Weapon);
			//RemoveWeapon(Weapon);
			Weapon->Destroy();
		}
	}
}

AXLWeapon* UXLWeaponManager::GetWeapon(int32 Weapon)
{
	return Inventory[Weapon];
}

int32 UXLWeaponManager::GetNextWeaponIndex(int32 Weapon)
{
	Weapon++;
	int32 InventorySize = Inventory.Num() - 1;
	return Weapon > InventorySize ? 0 : Weapon;
}

int32 UXLWeaponManager::GetPreviousWeaponIndex(int32 Weapon)
{
	Weapon--;
	int32 InventorySize = Inventory.Num() - 1;
	return Weapon < 0 ? InventorySize : Weapon;
}

void UXLWeaponManager::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXLWeaponManager, Inventory);
}
