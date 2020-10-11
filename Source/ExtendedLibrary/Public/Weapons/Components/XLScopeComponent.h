#pragma once

#include "Weapons/Components/Interfaces/XLTargetingComponent.h"
#include "XLScopeComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLScopeComponent : public UXLTargetingComponent
{
	GENERATED_BODY()

	UXLScopeComponent();

	void InitializeComponent() override;

private:
	UFUNCTION()
	void DetermineAction();

	UFUNCTION(Reliable, Client)
	void StartAim();

	UFUNCTION(Reliable, Client)
	void StopAim();
};
