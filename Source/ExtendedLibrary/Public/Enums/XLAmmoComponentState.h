#pragma once

UENUM(BlueprintType, Category = "XL|WeaponComponent")
namespace EAmmoComponentState
{
	enum Type
	{
		EmptyMagazine,
		FullMagazine,
		OutOfAmmo,
		PartialMagazine,
	};
}