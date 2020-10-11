#pragma once

#include "Weapons/Components/Interfaces/XLAmmoComponent.h"
#include "XLReloadComponent.generated.h"

class USoundCue;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLReloadComponent : public UXLAmmoComponent
{
	GENERATED_BODY()

public: 
    class AXLRangedWeapon* Owner;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* ReloadAnim;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* ReloadSound;

	FTimerHandle ReloadTimer;

public:
	UXLReloadComponent();

    void InitializeComponent() override;

	void ConsumeAmmo() override;

	void Reload() override;

	//UFUNCTION(Reliable, Server, WithValidation)
	//void ServerConsumeAmmo();

	//UFUNCTION(Reliable, Server, WithValidation)
	//void ServerReload(float ClipDelta);
};
