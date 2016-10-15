// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPlayerState.h"


AXLPlayerState::AXLPlayerState()
{
	WinningState = EWinningState::Playing;
	TeamNumber = 0;
	NumKills = 0;
	NumDeaths = 0;
	NumBulletsFired = 0;
	NumRocketsFired = 0;
}

void AXLPlayerState::Reset()
{
	Super::Reset();
}

void AXLPlayerState::SetTeamNum(int32 NewTeamNumber)
{
	TeamNumber = NewTeamNumber;
}

void AXLPlayerState::AddBulletsFired(int32 NumBullets)
{
	NumBulletsFired += NumBullets;
}

void AXLPlayerState::AddRocketsFired(int32 NumRockets)
{
	NumRocketsFired += NumRockets;
}

void AXLPlayerState::CopyProperties(APlayerState* PlayerState)
{
	Super::CopyProperties(PlayerState);

	AXLPlayerState* Player = Cast<AXLPlayerState>(PlayerState);
	if (Player)
	{
		Player->TeamNumber = TeamNumber;
	}
}

int32 AXLPlayerState::GetTeamNum() const
{
	return TeamNumber;
}

int32 AXLPlayerState::GetKills() const
{
	return NumKills;
}

int32 AXLPlayerState::GetDeaths() const
{
	return NumDeaths;
}

float AXLPlayerState::GetScore() const
{
	return Score;
}

int32 AXLPlayerState::GetNumBulletsFired() const
{
	return NumBulletsFired;
}

int32 AXLPlayerState::GetNumRocketsFired() const
{
	return NumRocketsFired;
}

void AXLPlayerState::ScoreKill(AXLPlayerState* Victim, int32 Points)
{
	NumKills++;
	ScorePoints(Points);
}

void AXLPlayerState::ScoreDeath(AXLPlayerState* KilledBy, int32 Points)
{
	NumDeaths++;
	ScorePoints(Points);
}

void AXLPlayerState::ScorePoints(int32 Points)
{
	/*ASSGameState* const MyGameState = Cast<ASSGameState>(GetWorld()->GameState);
	if (MyGameState && TeamNumber >= 0)
	{
		if (TeamNumber >= MyGameState->TeamScores.Num())
		{
			MyGameState->TeamScores.AddZeroed(TeamNumber - MyGameState->TeamScores.Num() + 1);
		}

		MyGameState->TeamScores[TeamNumber] += Points;
	}

	Score += Points;*/
}

void AXLPlayerState::InformAboutKill(class AXLPlayerState* KillerPlayerState, const UDamageType* KillerDamageType, class AXLPlayerState* KilledPlayerState)
{
	//id can be null for bots
	if (KillerPlayerState->UniqueId.IsValid())
	{
		//search for the actual killer before calling OnKill()	
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			AXLPlayerController* TestPC = Cast<AXLPlayerController>(*It);
			if (TestPC && TestPC->IsLocalController())
			{
				// a local player might not have an ID if it was created with CreateDebugPlayer.
				ULocalPlayer* LocalPlayer = Cast<ULocalPlayer>(TestPC->Player);
				TSharedPtr<const FUniqueNetId> LocalID = LocalPlayer->GetCachedUniqueNetId();
				if (LocalID.IsValid() && *LocalPlayer->GetCachedUniqueNetId() == *KillerPlayerState->UniqueId)
				{
					//TestPC->OnKill();
				}
			}
		}
	}
}

void AXLPlayerState::BroadcastDeath(class AXLPlayerState* KillerPlayerState, const UDamageType* KillerDamageType, class AXLPlayerState* KilledPlayerState)
{
	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
	{
		// all local players get death messages so they can update their huds.
		AXLPlayerController* TestPC = Cast<AXLPlayerController>(*It);
		if (TestPC && TestPC->IsLocalController())
		{
			//TestPC->OnDeathMessage(KillerPlayerState, this, KillerDamageType);
		}
	}
}



