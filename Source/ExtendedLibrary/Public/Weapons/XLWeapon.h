#pragma once

#include "Enums/XLFireMode.h"
#include "Enums/XLWeaponState.h"
#include "XLWeaponAnimationManager.h"
#include "XLWeaponSoundManager.h"
#include "XLItem.h"
#include "XLWeapon.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLWeapon : public AXLItem
{
	GENERATED_BODY()
	
public:
	AXLWeapon();

	void PostInitializeComponents() override;

	virtual void Tick(float DeltaSeconds) override;

	void Destroyed() override;

	virtual void SetOwner(AActor * NewOwner) override;

public: 

	UFUNCTION()
	void TogglePerspective();

	float StartUnequip() override;

	virtual void StartAttack();
	virtual void StopAttack();

	virtual void StartReload();
	virtual void StopReload();

	void StartMelee();
	void StopMelee();

	void Melee();

	void PlayWeaponSound();
	void StopWeaponSound();

	virtual void PlayFX() override;
	virtual void StopFX() override;

	virtual FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo);

};