// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Weapons/Components/XLAimingComponent.h"
#include "Weapons/Components/Interfaces/XLAmmoComponent.h"
#include "Items/XLItem.h"
#include "Weapons/Components/Interfaces/XLFireComponent.h"

UXLFireComponent::UXLFireComponent()
{
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
}

void UXLFireComponent::InitializeComponent()
{
	Super::InitializeComponent();

	AimingComponent = NewObject<UXLAimingComponent>(this, AimingComponentBP, FName(TEXT("AimingComponent")));
	AmmoComponent = NewObject<UXLAmmoComponent>(this, AmmoComponentBP, FName(TEXT("AmmoComponent")));

	AimingComponent->RegisterComponent();
	AmmoComponent->RegisterComponent();

	GetWeapon()->ItemPrimaryStateDelegate.AddDynamic(this, &UXLFireComponent::DetermineAction);
}

class AXLItem* UXLFireComponent::GetWeapon()
{
	return Cast<AXLItem>(GetOwner());
}

void UXLFireComponent::DetermineAction()
{
	// Do nothing. Handle in Children.
}
