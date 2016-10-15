// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "XLFindPointNearEnemy.generated.h"

/**
 * 
 */
UCLASS()
class UXLFindPointNearEnemy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

	UXLFindPointNearEnemy();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
