// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Items/XLItem.h"
#include "Managers/XLInventoryManager.h"

UXLInventoryManager::UXLInventoryManager()
{
	SetIsReplicatedByDefault(true);
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

AXLItem* UXLInventoryManager::GetItem(int32 index)
{
	if (index < Inventory.Num())
	{
		return Inventory[index];
	}
	return NULL;
}

void UXLInventoryManager::AddItem(TSubclassOf<class AXLItem> item, AXLCharacter* owner)
{
	if (item && owner && Inventory.Num() < InventorySize)
	{
		if (GetOwnerRole() == ROLE_Authority)
		{
			FActorSpawnParameters SpawnInfo;
			SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
			AXLItem* NewWeapon = GetWorld()->SpawnActor<AXLItem>(item, SpawnInfo);

			NewWeapon->SetOwningPawn(owner);
			Inventory.Add(NewWeapon);
		}
		else
		{
			ServerAddItem(item, owner);
		}
	}
	else
	{
		//UE_LOG(XLLog, Log, TEXT("Unable to equip item"));
	}
}

bool UXLInventoryManager::ServerAddItem_Validate(TSubclassOf<class AXLItem> item, AXLCharacter* owner)
{
	return true;
}
void UXLInventoryManager::ServerAddItem_Implementation(TSubclassOf<class AXLItem> item, AXLCharacter* owner)
{
	AddItem(item, owner);
}

void UXLInventoryManager::RemoveItem(int32 index, AXLCharacter* owner)
{
	if (index < Inventory.Num())
	{
		if (GetOwnerRole() == ROLE_Authority)
		{
			AXLCharacter* character = Cast<AXLCharacter>(owner);
			if (character->CurrentItem != Inventory[index])
			{
				Inventory.RemoveAt(index);
			}
		}
		else
		{
			ServerRemoveItem(index, owner);
		}
	}
	else
	{
		//UE_LOG(XLLog, Log, TEXT("Unable to remove item"));
	}
}

bool UXLInventoryManager::ServerRemoveItem_Validate(int32 index, AXLCharacter* owner)
{
	return true;
}
void UXLInventoryManager::ServerRemoveItem_Implementation(int32 index, AXLCharacter* owner)
{
	RemoveItem(index, owner);
}


void UXLInventoryManager::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXLInventoryManager, Inventory);
}
