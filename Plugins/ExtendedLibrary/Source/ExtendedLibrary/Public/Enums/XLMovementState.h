#pragma once

UENUM(BlueprintType, Category = Character)
namespace EMovementState
{
	enum Type
	{
		Idle,
		Moving,
		Sprinting,
		Jumping,
		Crouching,
		Prone,
		Dodging,
		Climbing
	};
}