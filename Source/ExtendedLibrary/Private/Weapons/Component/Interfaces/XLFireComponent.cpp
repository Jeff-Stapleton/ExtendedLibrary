// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLFireComponent.h"

UXLFireComponent::UXLFireComponent()
{
	bWantsInitializeComponent = true;
}

void UXLFireComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

class AXLRangedWeapon* UXLFireComponent::GetWeapon()
{
	return Cast<AXLRangedWeapon>(GetOwner());
}
