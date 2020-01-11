// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLCharacterCan.h"

bool XLCharacterCan::Jump(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::Move(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::Strafe(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::Turn(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::LookUp(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::StartCrouch(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::StopCrouch(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::StartProne(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::StopProne(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::StartSprint(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::StopSprint(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool XLCharacterCan::StartEquip(AXLCharacter* Character, int32 Weapon)
{
	if (Character && Character->GetController() && Weapon < Character->CharacterInventory->Inventory.Num() )
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::StopEquip(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::StartAim(AXLCharacter* Character)
{
	if (Character && Character->Controller && Character->CurrentItem < Character->CharacterInventory->Inventory.Num())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::StopAim(AXLCharacter* Character)
{
	if (Character && Character->Controller && Character->CurrentItem < Character->CharacterInventory->Inventory.Num())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::StartAttack(AXLCharacter* Character)
{
	if (Character && Character->Controller && Character->CurrentItem < Character->CharacterInventory->Inventory.Num())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::StopAttack(AXLCharacter* Character)
{
	if (Character && Character->Controller && Character->CurrentItem < Character->CharacterInventory->Inventory.Num())
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::StartReload(AXLCharacter* Character)
{
	if (Character && Character->Controller && Character->CurrentItem < Character->CharacterInventory->Inventory.Num())
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::StopReload(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::StartAbility(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool XLCharacterCan::StopAbility(AXLCharacter* Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLCharacterCan::Die(AXLCharacter * Character)
{
	if (Character && Character->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
