// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "XLPlayerState.generated.h"

UCLASS()
class AXLPlayerState : public APlayerState
{
	GENERATED_UCLASS_BODY()
public:

	UPROPERTY()
	int32 TeamNumber;

	int32 GetTeamNum() const;

};
