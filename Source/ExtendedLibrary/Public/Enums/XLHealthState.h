#pragma once

UENUM(BlueprintType, Category = Character)
namespace EHealthState
{
	enum Type
	{
		Alive,
		Dying,
		Dead
	};
}