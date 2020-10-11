#pragma once

#include "Interfaces/XLInteractionInterface.h"
#include "Camera/XLCamera.h"
#include "XLInteractionComponent.generated.h"

UCLASS()
class UXLInteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY()
	float InteractDistance = 50000.0f;

	UFUNCTION()
	void Inspect();

	UFUNCTION()
	void Interact();

	bool InteractTrace(FHitResult* Hit, FCollisionQueryParams* TraceParams);
};
