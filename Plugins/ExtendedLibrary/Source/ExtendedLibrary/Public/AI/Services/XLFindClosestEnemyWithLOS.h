// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "XLFindClosestEnemyWithLOS.generated.h"

/**
 * 
 */
UCLASS()
class UXLFindClosestEnemyWithLOS : public UBTService_BlackboardBase
{
	GENERATED_BODY()

	UXLFindClosestEnemyWithLOS();
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
