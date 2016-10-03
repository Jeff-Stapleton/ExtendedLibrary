#pragma once

#include "GameFramework/Actor.h"
#include "XLWeapon.generated.h"

UCLASS()
class AXLWeapon : public AActor
{
	GENERATED_BODY()
	
public:
	AXLWeapon();

	void PostInitializeComponents() override;

	void Destroyed() override;

	virtual void Tick(float DeltaSeconds) override;

	virtual bool StartAttack();
	virtual void StopAttack();

	virtual void StartReload();
	virtual void StopReload();

	void StartMelee();
	void StopMelee();

	void Melee();

	float PlayAnimation(class UAnimMontage* Animation, float InPlayRate = 1.f);
	void StopAnimation(class UAnimMontage* Animation);

	UAudioComponent* PlayWeaponSound(USoundCue* Sound);

	virtual void PlayWeaponFX();
	virtual void StopWeaponFX();

	void AttachMeshToPawn();
	void DetachMeshFromPawn();

};