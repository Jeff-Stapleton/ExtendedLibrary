// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPickupCan.h"

bool XLPickupCan::BePickedUp(AXLPickup* Pickup, AXLCharacter* Character)
{
	return Pickup->bIsActive && Character && Character->HealthState == EHealthState::Alive && !Pickup->IsPendingKill();
}
