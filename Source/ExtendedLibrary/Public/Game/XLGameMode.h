// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.
#pragma once
#include "GameFramework/GameMode.h"
#include "XLGameMode.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	AXLGameMode();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GameMode)
	TSubclassOf<APawn> BotPawnClass;

	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;
		
	virtual void RestartGame();

};



