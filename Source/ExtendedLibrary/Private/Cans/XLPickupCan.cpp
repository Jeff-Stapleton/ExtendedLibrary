// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPickupCan.h"

bool XLPickupCan::BePickedUp(AXLPickup* Pickup, AXLCharacter* Character)
{
	// current health > 0 is a hack 
	return Pickup->bIsActive && Character && Character->CharacterResources->CurrentHealth > 0 && !Pickup->IsPendingKill();
}
