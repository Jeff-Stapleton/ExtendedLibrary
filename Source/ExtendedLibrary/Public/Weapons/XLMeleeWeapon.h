#pragma once

#include "GameFramework/Actor.h"
#include "XLWeapon.h"
#include "XLMeleeWeapon.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLMeleeWeapon : public AXLItem
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, Replicated)
	TEnumAsByte<EWeaponState::Type> WeaponState;

	AXLMeleeWeapon();

	virtual void StartAttack();
	virtual void StopAttack();

	void SwingWeapon();

	FVector GetMeleeLocation();
	FRotator GetMeleeRotation();

	void ApplyAttackDamage(const FHitResult & Impact, const FVector & ShootDir);
	void ApplyAttackForce(const FHitResult& Impact);
};