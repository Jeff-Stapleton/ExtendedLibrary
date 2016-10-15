// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "XLPlayerState.generated.h"

UENUM(BlueprintType, Category = Character)
namespace EWinningState
{
	enum Type
	{
		Winner,
		Loser,
		Playing
	};
}

UCLASS()
class AXLPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	AXLPlayerState();

	virtual void Reset() override;
	
	void SetTeamNum(int32 NewTeamNumber);

	/** number of candies*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Candy)
	int32 CandyCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Winning)
	TEnumAsByte<EWinningState::Type> WinningState;

	/** player killed someone */
	void ScoreKill(AXLPlayerState* Victim, int32 Points);

	/** player died */
	void ScoreDeath(AXLPlayerState* KilledBy, int32 Points);

	/** get current team */
	int32 GetTeamNum() const;

	/** get number of kills */
	int32 GetKills() const;

	/** get number of deaths */
	int32 GetDeaths() const;

	/** get number of points */
	float GetScore() const;

	/** get number of bullets fired this match */
	int32 GetNumBulletsFired() const;

	/** get number of rockets fired this match */
	int32 GetNumRocketsFired() const;

	/** Sends kill (excluding self) to clients */
	UFUNCTION()
	void InformAboutKill(class AXLPlayerState* KillerPlayerState, const UDamageType* KillerDamageType, class AXLPlayerState* KilledPlayerState);

	/** broadcast death to local clients */
	UFUNCTION()
	void BroadcastDeath(class AXLPlayerState* KillerPlayerState, const UDamageType* KillerDamageType, class AXLPlayerState* KilledPlayerState);

	//We don't need stats about amount of ammo fired to be server authenticated, so just increment these with local functions
	void AddBulletsFired(int32 NumBullets);
	void AddRocketsFired(int32 NumRockets);

	virtual void CopyProperties(class APlayerState* PlayerState) override;
protected:

	/** team number */
	UPROPERTY()
	int32 TeamNumber;

	/** number of kills */
	UPROPERTY()
	int32 NumKills;

	/** number of deaths */
	UPROPERTY()
	int32 NumDeaths;

	/** number of bullets fired this match */
	UPROPERTY()
	int32 NumBulletsFired;

	/** number of rockets fired this match */
	UPROPERTY()
	int32 NumRocketsFired;

	/** helper for scoring points */
	void ScorePoints(int32 Points);
	
	
};
