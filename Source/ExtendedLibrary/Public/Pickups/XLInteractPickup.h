#pragma once

#include "Interfaces/XLInteractionInterface.h"
#include "Pickups/XLPickup.h"
#include "XLInteractPickup.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLInteractPickup : public AXLPickup, public IXLInteractionInterface
{
	GENERATED_UCLASS_BODY()

public:

	void OnInspect_Implementation(AActor* InteractingActor);

	void OnInteract_Implementation(AActor* InteractingActor);

};
