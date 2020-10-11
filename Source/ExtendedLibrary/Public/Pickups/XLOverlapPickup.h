#pragma once

#include "Pickups/XLPickup.h"
#include "XLOverlapPickup.generated.h"

class USphereComponent;

UCLASS()
class EXTENDEDLIBRARY_API AXLOverlapPickup : public AXLPickup
{
	GENERATED_UCLASS_BODY()

	virtual void PostInitializeComponents() override;

public:
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
	USphereComponent* OverlapVolume;

	//UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	//UCapsuleComponent* OverlapVolume;

	virtual void NotifyActorBeginOverlap(class AActor* Other) override;

};
