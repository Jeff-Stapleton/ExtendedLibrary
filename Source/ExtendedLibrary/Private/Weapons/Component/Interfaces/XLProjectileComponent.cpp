#include "ExtendedLibraryPCH.h"
#include "XLProjectileComponent.h"

UXLProjectileComponent::UXLProjectileComponent()
{
	bWantsInitializeComponent = true;
}

void UXLProjectileComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

class AXLRangedWeapon* UXLProjectileComponent::GetWeapon()
{
	return Cast<AXLRangedWeapon>(GetOwner());
}