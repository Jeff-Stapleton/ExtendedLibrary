// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "XLSelectNextPatrolPoint.generated.h"

// Bot AI task that tries to find a location near the current enemy
UCLASS()
class UXLSelectNextPatrolPoint : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()

	int32 Position = 0;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
