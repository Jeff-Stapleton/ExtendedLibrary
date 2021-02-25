// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "XLAttributeSetTableRow.generated.h"

/**
 * 
 */
USTRUCT(BlueprintType)
struct EXTENDEDLIBRARY_API FXLAttributeSetTableRow : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:

	FXLAttributeSetTableRow()
		: base(0)
		, max(0)
	{}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	int32 base;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = LevelUp)
	int32 max;
};
