#pragma once

UENUM(BlueprintType, Category = Weapon)
namespace EWeaponState
{
	enum Type
	{
		Idle,
		Firing,
		Reloading,
		Meleeing,
		OutOfAmmo
	};
}