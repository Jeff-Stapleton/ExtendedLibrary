#pragma once

UENUM(BlueprintType, Category = "XL|Enums")
namespace EItemPrimaryState
{
	enum Type
	{
		Idle,
		Activated,
		Reloading,
		Meleeing,
		OutOfAmmo,
		NotReady
	};
}