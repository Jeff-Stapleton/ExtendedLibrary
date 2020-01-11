#pragma once

#include "Components/ActorComponent.h"
#include "XLReloadComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLReloadComponent : public UActorComponent
{
	GENERATED_BODY()

    class AXLRangedWeapon* Owner;

public:
	UXLReloadComponent();

    void InitializeComponent() override;

	virtual void OnRegister() override;

	UFUNCTION()
	void ConsumeAmmo();

	UFUNCTION()
	void Reload();

};