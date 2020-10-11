#include "ExtendedLibraryPCH.h"
#include "Weapons/XLRangedWeapon.h"
#include "Weapons/Components/Interfaces/XLProjectileComponent.h"

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
