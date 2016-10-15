// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "XLGameMode.h"

AXLGameMode::AXLGameMode(const class FObjectInitializer& PCIP)
	: Super(PCIP)
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnOb(TEXT("/Game/Characters/Player/Hero/Hero"));
	static ConstructorHelpers::FClassFinder<APawn> BotPawnOb(TEXT("/Game/Characters/AI/Enemy1/Enemy1"));

	BotPawnClass = BotPawnOb.Class;
	DefaultPawnClass = PlayerPawnOb.Class;
	PlayerControllerClass = AXLPlayerController::StaticClass();
	PlayerStateClass = AXLPlayerState::StaticClass();
	GameStateClass = AXLGameState::StaticClass();

	MinRespawnDelay = 120.0f;

	bAllowBots = false;
	bTeamEliminated = false;
	bUseSeamlessTravel = true;
	bStartPlayersAsSpectators = false;
	//bDelayedStart = false;
	InactivePlayerStateLifeSpan = 30.0f;
}

FString AXLGameMode::GetBotsCountOptionName()
{
	return FString(TEXT("Bots"));
}

void AXLGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	const int32 BotsCountOptionValue = UGameplayStatics::GetIntOption(Options, GetBotsCountOptionName(), 0);
	SetAllowBots(BotsCountOptionValue > 0 ? true : false, BotsCountOptionValue);
	Super::InitGame(MapName, Options, ErrorMessage);

	const UGameInstance* GameInstance = GetGameInstance();
	//if (GameInstance && Cast<UXLGameInstance>(GameInstance)->GetIsOnline())
	//{
	//	bPauseable = false;
	//}
}

void AXLGameMode::SetAllowBots(bool bInAllowBots, int32 InMaxBots)
{
	bAllowBots = 0;
	MaxBots = 0;
}

/** Returns game session class to use */
TSubclassOf<AGameSession> AXLGameMode::GetGameSessionClass() const
{
	return AXLGameSession::StaticClass();
}

void AXLGameMode::PreInitializeComponents()
{
	Super::PreInitializeComponents();

	GetWorldTimerManager().SetTimer(TimerHandle_DefaultTimer, this, &AXLGameMode::DefaultTimer, GetWorldSettings()->GetEffectiveTimeDilation(), true);
}

void AXLGameMode::DefaultTimer()
{
	// don't update timers for Play In Editor mode, it's not real match
	if (GetWorld()->IsPlayInEditor())
	{
		// start match if necessary.
		if (GetMatchState() == MatchState::WaitingToStart)
		{
			StartMatch();
		}
		//return;
	}

	AXLGameState* const MyGameState = Cast<AXLGameState>(GameState);
	if (MyGameState)
	{
		MyGameState->RemainingTime--;
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			AXLPlayerCharacter* TestPawn = Cast<AXLPlayerCharacter>(*It);
			if (TestPawn)
			{
				AXLPlayerState* MyState = Cast<AXLPlayerState>(TestPawn->Controller->PlayerState);
				if (MyState->CandyCount >= 35)
				{
					MyState->WinningState = EWinningState::Winner;
					if (GetMatchState() == MatchState::WaitingPostMatch)
					{
						RestartGame();
					}
					else if (GetMatchState() == MatchState::InProgress)
					{
						FinishMatch();

						// Send end round events
						for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
						{
							AXLPlayerController* PlayerController = Cast<AXLPlayerController>(*It);

							if (PlayerController && MyGameState)
							{
								AXLPlayerState* PlayerState = Cast<AXLPlayerState>((*It)->PlayerState);
								const bool bIsWinner = IsWinner(PlayerState);

								//PlayerController->ClientSendRoundEndEvent(bIsWinner, MyGameState->ElapsedTime);
							}
						}
					}
					else if (GetMatchState() == MatchState::WaitingToStart)
					{
						StartMatch();
					}
				}
			}
		}
	}
}

void AXLGameMode::HandleMatchHasStarted()
{
	Super::HandleMatchHasStarted();

	AXLGameState* const MyGameState = Cast<AXLGameState>(GameState);
	MyGameState->RemainingTime = RoundTime;

	// notify players
	for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		AXLPlayerController* PC = Cast<AXLPlayerController>(*It);
		if (PC)
		{
			PC->ClientGameStarted();
		}
	}
}

void AXLGameMode::HandleMatchIsWaitingToStart()
{
	if (bDelayedStart)
	{
		// start warmup if needed
		AXLGameState* const MyGameState = Cast<AXLGameState>(GameState);
		if (MyGameState && MyGameState->RemainingTime == 0)
		{
			const bool bWantsMatchWarmup = GetWorld()->IsPlayInEditor();
			if (bWantsMatchWarmup && WarmupTime > 0)
			{
				MyGameState->RemainingTime = WarmupTime;
			}
			else
			{
				MyGameState->RemainingTime = 0.0f;
			}
		}
	}
}

void AXLGameMode::FinishMatch()
{
	AXLGameState* const MyGameState = Cast<AXLGameState>(GameState);
	if (IsMatchInProgress())
	{
		EndMatch();
		if (Role == ROLE_Authority)
		{
			DetermineMatchWinner();
		}

		// notify players
		for (FConstControllerIterator It = GetWorld()->GetControllerIterator(); It; ++It)
		{
			AXLPlayerState* PlayerState = Cast<AXLPlayerState>((*It)->PlayerState);
			const bool bIsWinner = IsWinner(PlayerState);

			(*It)->GameHasEnded(NULL, bIsWinner);
		}

		// lock all pawns
		// pawns are not marked as keep for seamless travel, so we will create new pawns on the next match rather than
		// turning these back on.
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			(*It)->TurnOff();
		}

		// set up to restart the match
		bTeamEliminated = false;
		MyGameState->RemainingTime = TimeBetweenMatches;
	}
}

void AXLGameMode::RequestFinishAndExitToMainMenu()
{
	FinishMatch();

	//UXLGameInstance* const GameInstance = Cast<UXLGameInstance>(GetGameInstance());
	//if (GetGameInstance())
	//{
	//	GameInstance->RemoveSplitScreenPlayers();
	//}

	AXLPlayerController* LocalPrimaryController = nullptr;
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		AXLPlayerController* Controller = Cast<AXLPlayerController>(*Iterator);

		if (Controller == NULL)
		{
			continue;
		}

		if (!Controller->IsLocalController())
		{
			const FString RemoteReturnReason = NSLOCTEXT("NetworkErrors", "HostHasLeft", "Host has left the game.").ToString();
			//Controller->ClientReturnToMainMenu(RemoteReturnReason);
		}
		else
		{
			LocalPrimaryController = Controller;
		}
	}

	// GameInstance should be calling this from an EndState.  So call the PC function that performs cleanup, not the one that sets GI state.
	if (LocalPrimaryController != NULL)
	{
		//LocalPrimaryController->HandleReturnToMainMenu();
	}
}

void AXLGameMode::DetermineMatchWinner()
{
	// nothing to do here
}

void AXLGameMode::CheckTeamElimination()
{
	// nothing to do here
}

bool AXLGameMode::IsWinner(class AXLPlayerState* PlayerState) const
{
	return false;
}

void AXLGameMode::PreLogin(const FString& Options, const FString& Address, const TSharedPtr<const FUniqueNetId>& UniqueId, FString& ErrorMessage)
{
	AXLGameState* const MyGameState = Cast<AXLGameState>(GameState);
	const bool bMatchIsOver = MyGameState && MyGameState->HasMatchEnded();
	if (bMatchIsOver)
	{
		ErrorMessage = TEXT("Match is over!");
	}
	else
	{
		// GameSession can be NULL if the match is over
		Super::PreLogin(Options, Address, UniqueId, ErrorMessage);
	}
}


void AXLGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	// update spectator location for client
	AXLPlayerController* NewPC = Cast<AXLPlayerController>(NewPlayer);
	if (NewPC && NewPC->GetPawn() == NULL)
	{
		//NewPC->ClientSetSpectatorCamera(NewPC->GetSpawnLocation(), NewPC->GetControlRotation());
	}

	// notify new player if match is already in progress
	if (NewPC && IsMatchInProgress())
	{
		NewPC->ClientGameStarted();
		NewPC->ClientStartOnlineGame();
	}
}

void AXLGameMode::Killed(AController* Killer, AController* KilledPlayer, APawn* KilledPawn, const UDamageType* DamageType)
{
	AXLPlayerState* KillerPlayerState = Killer ? Cast<AXLPlayerState>(Killer->PlayerState) : NULL;
	AXLPlayerState* VictimPlayerState = KilledPlayer ? Cast<AXLPlayerState>(KilledPlayer->PlayerState) : NULL;

	if (KillerPlayerState && KillerPlayerState != VictimPlayerState)
	{
		KillerPlayerState->ScoreKill(VictimPlayerState, KillScore);
		KillerPlayerState->InformAboutKill(KillerPlayerState, DamageType, VictimPlayerState);
	}
	if (VictimPlayerState)
	{
		VictimPlayerState->ScoreDeath(KillerPlayerState, DeathScore);
		VictimPlayerState->BroadcastDeath(KillerPlayerState, DamageType, VictimPlayerState);
	}
	//CheckTeamElimination();
}

float AXLGameMode::ModifyDamage(float Damage, AActor* DamagedActor, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) const
{
	float ActualDamage = Damage;

	AXLCharacter* DamagedPawn = Cast<AXLCharacter>(DamagedActor);
	if (DamagedPawn && EventInstigator)
	{
		AXLPlayerState* DamagedPlayerState = Cast<AXLPlayerState>(DamagedPawn->PlayerState);
		AXLPlayerState* InstigatorPlayerState = Cast<AXLPlayerState>(EventInstigator->PlayerState);

		// disable friendly fire
		if (!CanDealDamage(InstigatorPlayerState, DamagedPlayerState))
		{
			ActualDamage = 0.0f;
		}

		// scale self instigated damage
		if (InstigatorPlayerState == DamagedPlayerState)
		{
			ActualDamage *= DamageSelfScale;
		}
	}

	return ActualDamage;
}

bool AXLGameMode::CanDealDamage(class AXLPlayerState* DamageInstigator, class AXLPlayerState* DamagedPlayer) const
{
	return true;
}

bool AXLGameMode::AllowCheats(APlayerController* P)
{
	return false;
}

bool AXLGameMode::ShouldSpawnAtStartSpot(AController* Player)
{
	return false;
}

UClass* AXLGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}

AActor* AXLGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	TArray<APlayerStart*> PreferredSpawns;
	TArray<APlayerStart*> FallbackSpawns;

	APlayerStart* BestStart = NULL;
	for (TActorIterator<APlayerStart> It(GetWorld()); It; ++It)
	{
		APlayerStart* TestSpawn = *It;
		if (TestSpawn->IsA<APlayerStartPIE>())
		{
			// Always prefer the first "Play from Here" PlayerStart, if we find one while in PIE mode
			BestStart = TestSpawn;
			break;
		}
		else
		{
			if (IsSpawnpointAllowed(TestSpawn, Player))
			{
				if (IsSpawnpointPreferred(TestSpawn, Player))
				{
					PreferredSpawns.Add(TestSpawn);
				}
				else
				{
					FallbackSpawns.Add(TestSpawn);
				}
			}
		}
	}


	if (BestStart == NULL)
	{
		if (PreferredSpawns.Num() > 0)
		{
			BestStart = PreferredSpawns[FMath::RandHelper(PreferredSpawns.Num())];
		}
		else if (FallbackSpawns.Num() > 0)
		{
			BestStart = FallbackSpawns[FMath::RandHelper(FallbackSpawns.Num())];
		}
	}

	return BestStart ? BestStart : Super::ChoosePlayerStart_Implementation(Player);
}

bool AXLGameMode::IsSpawnpointAllowed(APlayerStart* SpawnPoint, AController* Player) const
{
	/*AXLTeamStart* XLSpawnPoint = Cast<AXLTeamStart>(SpawnPoint);
	if (XLSpawnPoint)
	{
		if (XLSpawnPoint->bNotForPlayers)
		{
			return false;
		}
		return true;
	}

	return false;*/
	return true;
}

bool AXLGameMode::IsSpawnpointPreferred(APlayerStart* SpawnPoint, AController* Player) const
{
	ACharacter* MyPawn = Cast<ACharacter>((*DefaultPawnClass)->GetDefaultObject<ACharacter>());
	if (MyPawn)
	{
		const FVector SpawnLocation = SpawnPoint->GetActorLocation();
		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			ACharacter* OtherPawn = Cast<ACharacter>(*It);
			if (OtherPawn && OtherPawn != MyPawn)
			{
				const float CombinedHeight = (MyPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() + OtherPawn->GetCapsuleComponent()->GetScaledCapsuleHalfHeight()) * 2.0f;
				const float CombinedRadius = MyPawn->GetCapsuleComponent()->GetScaledCapsuleRadius() + OtherPawn->GetCapsuleComponent()->GetScaledCapsuleRadius();
				const FVector OtherLocation = OtherPawn->GetActorLocation();

				// check if player start overlaps this pawn
				if (FMath::Abs(SpawnLocation.Z - OtherLocation.Z) < CombinedHeight && (SpawnLocation - OtherLocation).Size2D() < CombinedRadius)
				{
					return false;
				}
			}
		}
	}
	else
	{
		return false;
	}

	return true;
}

void AXLGameMode::RestartGame()
{
	Super::RestartGame();
}