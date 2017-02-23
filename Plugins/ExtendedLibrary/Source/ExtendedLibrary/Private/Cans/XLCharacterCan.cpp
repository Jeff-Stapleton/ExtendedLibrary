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
