#pragma once

#include "XLRangedWeapon.h"
#include "XLCharacter.h"
#include "XLPlayerController.h"
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

	/** Weapon ranges */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float MaxRange = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float Bloom = 10.0f;

public:
	FVector GetAdjustedAim();

protected:
	FVector GetAimDestination();
	FVector GetAimOrigin();
	FVector Trace(FVector Origin, FVector Target);
};