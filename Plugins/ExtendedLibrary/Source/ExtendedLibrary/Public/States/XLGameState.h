// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameState.h"
#include "XLGameState.generated.h"

/**
 * 
 */
UCLASS()
class AXLGameState : public AGameState
{
	GENERATED_BODY()

	AXLGameState();

public:

	UPROPERTY(Transient)
	int32 NumTeams;

	UPROPERTY(Transient)
	TArray<int32> TeamScores;

	UPROPERTY(Transient)
	int32 RemainingTime;

	UPROPERTY(Transient)
	bool bTimerPaused;

	void RequestFinishAndExitToMainMenu();
	
};
