#pragma once

#include "Weapons/Components/Interfaces/XLAmmoComponent.h"
#include "XLShellAmmoComponent.generated.h"

class USoundCue;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLShellAmmoComponent : public UXLAmmoComponent
{
	GENERATED_BODY()

public:
	/** If true the weapon can always be reloaded to full clip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	bool InfiniteAmmo = false;

	/** If true the weapon never has to be reloaded  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	bool InfiniteClip = false;

	/** The max number of total ammo */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxAmmo = 125.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float ReloadDuration = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* ReloadAnim;

	UPROPERTY(EditDefaultsOnly, Category = Sound)
	USoundCue* ReloadSound;

	FTimerHandle ReloadTimer;

private:
	float AnimationRate = 1.0f;

public: 
	UXLShellAmmoComponent();

    void InitializeComponent() override;

	void DetermineAction();

	void ConsumeAmmo() override;

	void Reload() override;

	UFUNCTION()
	void LoadShell();

};
