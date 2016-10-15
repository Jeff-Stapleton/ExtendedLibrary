// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLGameState.h"

AXLGameState::AXLGameState()
{
	NumTeams = 0;
	RemainingTime = 0;
	bTimerPaused = false;
}

void AXLGameState::RequestFinishAndExitToMainMenu()
{
	AXLPlayerController* const PrimaryPC = Cast<AXLPlayerController>(GetGameInstance()->GetFirstLocalPlayerController());
	if (PrimaryPC)
	{
		check(PrimaryPC->GetNetMode() == ENetMode::NM_Client);
		//PrimaryPC->HandleReturnToMainMenu();
	}
}

