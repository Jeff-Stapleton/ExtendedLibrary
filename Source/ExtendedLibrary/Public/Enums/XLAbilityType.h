#pragma once

UENUM(BlueprintType, Category = Ability)
enum class EAbilityType : uint8
{
	None,
	Confirm,
	Cancel,
	Jump,
	Sprint
};