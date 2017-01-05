// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "XLGameInstance.generated.h"

UCLASS(config = Game)
class UXLGameInstance : public UGameInstance
{
public:
	GENERATED_BODY()
		
public:
	UXLGameInstance();

	bool Tick(float DeltaSeconds);

	virtual void Init() override;
	virtual void Shutdown() override;
	virtual void StartGameInstance() override;

	/*void FinishJoinSession(EOnJoinSessionCompleteResult::Type Result);
	bool JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult);*/

};
