#pragma once

UENUM(BlueprintType, Category = Character)
namespace EPostureState
{
	enum Type
	{
		Airborne,
		Crouching,
		Prone,
		Standing,
	};
}