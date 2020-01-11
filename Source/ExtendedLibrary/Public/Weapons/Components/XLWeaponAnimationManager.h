#pragma once

#include "Components/ActorComponent.h"
#include "XLItemAnimationManager.h"
#include "XLWeaponAnimationManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLWeaponAnimationManager : public UXLItemAnimationManager
{
	GENERATED_BODY()

	class AXLRangedWeapon* Owner;

public:

	/** melee animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* MeleeAnim;

	/** reload animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* ReloadAnim;

protected:

	FTimerHandle ReloadTimer;

public:
	UXLWeaponAnimationManager();

	void InitializeComponent() override;

	UFUNCTION()
	void DetermineAction();

protected:
	void StartReload();
	void FinishReload();

private:
	float PlayAnimation(UAnimMontage* Animation, float Duration = 0.5f);
	void StopAnimation();
};