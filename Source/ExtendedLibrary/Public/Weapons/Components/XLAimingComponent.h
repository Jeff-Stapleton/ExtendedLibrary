#pragma once

#include "ExtendedLibraryPCH.h"
#include "XLRangedWeapon.h"
#include "XLCamera.h"
#include "XLAIController.h"
#include "XLAimingComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	UXLAimingComponent();

	void InitializeComponent() override;

public:
	class AXLRangedWeapon* Owner;

public:
	FVector GetAdjustedAim();

protected:
	FVector GetAimDestination();
	FVector GetAimOrigin();
	FVector Trace(FVector Origin, FVector Target);
};