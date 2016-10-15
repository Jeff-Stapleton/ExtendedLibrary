#pragma once

#include "Components/ActorComponent.h"
#include "XLWeaponSoundManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLWeaponSoundManager : public UActorComponent
{
	GENERATED_BODY()

public:

	/** equip animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* EquipAnim;

	/** holster animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* UnEquipAnim;

	/** melee animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* MeleeAnim;

	/** reload animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* ReloadAnim;

public:
	UXLWeaponSoundManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};