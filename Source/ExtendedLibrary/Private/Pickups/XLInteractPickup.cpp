#include "ExtendedLibraryPCH.h"
#include "Pickups/XLInteractPickup.h"

AXLInteractPickup::AXLInteractPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void AXLInteractPickup::OnInspect_Implementation(AActor* Instigator)
{
	// Display interact keybinding and pickup name
}

void AXLInteractPickup::OnInteract_Implementation(AActor* Instigator)
{
	AXLCharacter* Pawn = Cast<AXLCharacter>(Instigator);
	if (XLPickupCan::BePickedUp(this, Pawn))
	{
		OnPickedUp(Cast<AXLCharacter>(Pawn));
	}
}

void AXLInteractPickup::OnPickedUp(class AXLCharacter* Pawn)
{
	Super::OnPickedUp(Pawn);
}