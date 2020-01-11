// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLInventoryManager.h"

UXLInventoryManager::UXLInventoryManager()
{
	bReplicates = true;
}

void UXLInventoryManager::DestroyInventory()
{
	if (GetOwnerRole() < ROLE_Authority)
	{
		return;
	}

	// remove all items from inventory and destroy them
	for (int32 i = Inventory.Num() - 1; i >= 0; i--)
	{
		AXLItem* Item = Inventory[i];
		if (Item)
		{
			Inventory.RemoveSingle(Item);
			//RemoveWeapon(Weapon);
			Item->Destroy();
		}
	}
}

AXLItem* UXLInventoryManager::GetItem(int32 item)
{
	if (item < Inventory.Num())
	{
		return Inventory[item];
	}
	return NULL;
}

void UXLInventoryManager::AddItem(TSubclassOf<class AXLItem> item, AActor* owner)
{
	if (item && owner && Inventory.Num() < InventorySize)
	{
		if (GetOwnerRole() == ROLE_Authority)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AXLWeapon* NewWeapon = GetWorld()->SpawnActor<AXLWeapon>(item, SpawnInfo);

			NewWeapon->SetOwner(owner);
			Inventory.Add(NewWeapon);
		}
		else
		{
			ServerAddItem(item, owner);
		}
	}
	else
	{
		UE_LOG(XLLog, Log, TEXT("Unable to equip item"));
	}
}

bool UXLInventoryManager::ServerAddItem_Validate(TSubclassOf<class AXLItem> item, AActor* owner)
{
	return true;
}
void UXLInventoryManager::ServerAddItem_Implementation(TSubclassOf<class AXLItem> item, AActor* owner)
{
	AddItem(item, owner);
}


void UXLInventoryManager::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXLInventoryManager, Inventory);
}
