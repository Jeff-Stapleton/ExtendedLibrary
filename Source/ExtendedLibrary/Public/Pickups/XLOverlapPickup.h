#pragma once

#include "Pickups/XLPickup.h"
#include "XLOverlapPickup.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLOverlapPickup : public AXLPickup
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	UCapsuleComponent* OverlapVolume;

	virtual void NotifyActorBeginOverlap(class AActor* Other) override;

	virtual void OnPickedUp(class AXLCharacter* Pawn) override;

};
