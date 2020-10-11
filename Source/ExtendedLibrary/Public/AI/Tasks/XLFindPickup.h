// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "Game/XLGameMode.h"
#include "XLFindPickup.generated.h"

// Bot AI Task that attempts to locate a pickup 
UCLASS()
class UXLFindPickup : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()
		
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
