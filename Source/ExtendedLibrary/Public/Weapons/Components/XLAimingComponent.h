#pragma once

#include "Weapons/XLRangedWeapon.h"
#include "Characters/XLCharacter.h"
#include "Controllers/XLPlayerController.h"
#include "Controllers/XLAIController.h"
#include "XLAimingComponent.generated.h"

class AXLItem;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLAimingComponent : public UActorComponent
{
	GENERATED_BODY()

	UXLAimingComponent();

	void InitializeComponent() override;

public:
	AXLItem* Owner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float MaxRange = 10000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float Bloom = 10.0f;

public:
	FVector GetAdjustedAim();
	FVector GetAimDestination();
	FVector GetAimOrigin();
	FVector Trace(FVector Origin, FVector Target);
};
