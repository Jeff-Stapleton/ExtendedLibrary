// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "GameFramework/PlayerState.h"
#include "XLPlayerState.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AXLPlayerState();

	UPROPERTY()
	int32 TeamNumber;

	int32 GetTeamNum() const;

};
