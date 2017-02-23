#pragma once

UENUM(BlueprintType, Category = Character)
namespace EActionState
{
	enum Type
	{
		Climbing,
		Dodging,
		Jumping,
		None,
		Sprinting,
	};
}