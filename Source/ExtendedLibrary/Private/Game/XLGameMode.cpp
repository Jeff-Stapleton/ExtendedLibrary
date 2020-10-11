// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "Game/XLGameMode.h"
#include "Characters/XLCharacter.h"
#include "Controllers/XLPlayerController.h"
#include "Online/XLPlayerState.h"

AXLGameMode::AXLGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/ExtendedLibrary/Characters/Humanoid/Blueprints/Humanoid"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;		
	}
	else
	{
		DefaultPawnClass = AXLCharacter::StaticClass();
	}

	static ConstructorHelpers::FClassFinder<APawn> BotPawnBPClass(TEXT("/ExtendedLibrary/Characters/Humanoid/Blueprints/AI"));
	if (BotPawnBPClass.Class != NULL)
	{
		BotPawnClass = BotPawnBPClass.Class;
	}

	PlayerControllerClass = AXLPlayerController::StaticClass();
	PlayerStateClass = AXLPlayerState::StaticClass();
	//GameStateClass = AXLGameState::StaticClass();

	bUseSeamlessTravel = true;
}

void AXLGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);

	const UGameInstance* GameInstance = GetGameInstance();
}

void AXLGameMode::RestartGame()
{
	// Hide the scoreboard too !
	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AXLPlayerController* PlayerController = Cast<AXLPlayerController>(*It);
		if (PlayerController != nullptr)
		{
			/*AShooterHUD* ShooterHUD = Cast<AShooterHUD>(PlayerController->GetHUD());
			if (ShooterHUD != nullptr)
			{
				// Passing true to bFocus here ensures that focus is returned to the game viewport.
				ShooterHUD->ShowScoreboard(false, true);
			}*/
		}
	}

	Super::RestartGame();
}
