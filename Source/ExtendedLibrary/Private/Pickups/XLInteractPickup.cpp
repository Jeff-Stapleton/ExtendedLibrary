#include "ExtendedLibraryPCH.h"
#include "Cans/XLPickupCan.h"
#include "Pickups/XLInteractPickup.h"

AXLInteractPickup::AXLInteractPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AXLInteractPickup::OnInspect_Implementation(AActor* InteractingActor)
{
	// Display interact keybinding and pickup name
}

void AXLInteractPickup::OnInteract_Implementation(AActor* InteractingActor)
{
	AXLCharacter* Pawn = Cast<AXLCharacter>(InteractingActor);
	if (XLPickupCan::BePickedUp(this, Pawn))
	{
		PickedUp(Cast<AXLCharacter>(Pawn));
	}
}
