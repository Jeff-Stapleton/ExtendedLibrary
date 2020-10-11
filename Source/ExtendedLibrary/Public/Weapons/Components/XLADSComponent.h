#pragma once

#include "Weapons/Components/Interfaces/XLTargetingComponent.h"
#include "XLADSComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLADSComponent : public UXLTargetingComponent
{
	GENERATED_BODY()

	UXLADSComponent();

	void InitializeComponent() override;

private:
	UFUNCTION()
	void DetermineAction();

	UFUNCTION(Reliable, Client)
	void StartAim();

	UFUNCTION(Reliable, Client)
	void StopAim();
};
