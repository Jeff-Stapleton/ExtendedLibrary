#pragma once

#include "GameFramework/Actor.h"
#include "XLRangedWeapon.h"
#include "XLVehicleRangedWeapon.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLVehicleRangedWeapon : public AXLRangedWeapon
{
	GENERATED_BODY()
	
public:
	AXLVehicleRangedWeapon();

	virtual void Tick(float DeltaSeconds) override;

	virtual void Destroyed() override;

};