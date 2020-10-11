// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Items/XLItem.h"
#include "Weapons/Components/Interfaces/XLTargetingComponent.h"

class AXLItem* UXLTargetingComponent::GetWeapon()
{
	return Cast<AXLItem>(GetOwner());
}
