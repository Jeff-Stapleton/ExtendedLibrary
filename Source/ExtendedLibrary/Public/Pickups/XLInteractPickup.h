#pragma once

#include "Interfaces/XLInteractionInterface.h"
#include "Pickups/XLPickup.h"
#include "XLInteractPickup.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLInteractPickup : public AXLPickup, public IXLInteractionInterface
{
	GENERATED_UCLASS_BODY()

public:

	void OnInspect_Implementation(AActor* MyInstigator);

	void OnInteract_Implementation(AActor* MyInstigator);

	virtual void OnPickedUp(class AXLCharacter* Pawn) override;

};
