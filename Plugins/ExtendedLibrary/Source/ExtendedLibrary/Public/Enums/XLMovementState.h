#pragma once

UENUM(BlueprintType, Category = Character)
namespace EMovementState
{
	enum Type
	{
		AFK,
		Idle,
		Moving,
	};
}