#pragma once

#include "Structs/XLRecoilData.h"
#include "XLWeaponStats.generated.h"

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class UXLWeaponStats : public UActorComponent
{
	GENERATED_BODY()

public:

	/** The max amount of damage dealt possible */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float MaxDamage = 19.0f;

	/** The minimum amount of damage dealt possible */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float MinDamage = 19.0f;

	/** type of damage */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	TSubclassOf<UDamageType> DamageType;

	/** The amount of force the attack applies */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float Force = 10000.0f;

	/** Weapon ranges */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float MaxRange = 10000.0f;

	/** The amount of time that must pass before being able to attack again */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float TimeBetweenAttacks = 0.12f;

	///////////////////////////////////// AMMO /////////////////////////////////////

	/** If true the weapon can always be reloaded to full clip */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	bool InfiniteAmmo = false;

	/** If true the weapon never has to be reloaded  */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	bool InfiniteClip = false;

	/** The max number of total ammo */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxAmmo = 125.0f;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = Resources)
	float CurrentAmmo;

	/** The amount of ammo in each clip */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxClipAmmo = 25.0f;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = Resources)
	float CurrentClipAmmo;

	///////////////////////////////////// RANGED STATS /////////////////////////////////////

	/** The number of projectiles that are fired when attacking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float ShotNumber = 1.0f;

	/** The max spread, in degrees from center, an attack will vary in any direction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float MaxSpread = 4.15f;

	/** The initial spread, in degrees from center, an attack will vary in any direction */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float MinSpread = 4.15f;

	UPROPERTY(BlueprintReadWrite)
	float CurrentSpread = 0.0f;

	/** The rate the spread will grow, in degree from center, when continuously attacking */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float SpreadRate;

	/** Modifies the spread by this factor when aiming down the sights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float SpreadModifier = 1.0f;

	/** The amount the cursor moves when firing. Negative is left or up and positive is right or down */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	TArray<FRecoilData> RecoilPattern;

	/** The amount the weapon pulls vertically when attacking, Negative for up, positive for down */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float VerticalRecoil;

	/** The amount the weapon pulls horizontally when attacking, Negative for left, positive for right */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float HorizontalRecoil;

	/** The speed at which the recoil interpolates from point A to point B */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float RecoilSpeed = 50.0f;

	/** Modifies the recoil by this factor when aiming down the sights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float RecoilModifier = 1.0f;

	/** The speed at which the settling interpolates from point A to point B */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float SettlingSpeed = 10.0f;

	/** Defines the field of view for when the aiming down the sights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float TargetingFOV = 45.0f;

public:

	UXLWeaponStats();

	void BeginPlay() override;
};
