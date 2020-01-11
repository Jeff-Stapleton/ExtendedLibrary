// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "XLSelectNextPatrolPoint.h"
#include "XLAIController.h"
#include "XLAICharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"


UXLSelectNextPatrolPoint::UXLSelectNextPatrolPoint(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
}

EBTNodeResult::Type UXLSelectNextPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AXLAIController* MyController = Cast<AXLAIController>(OwnerComp.GetAIOwner());
	if (MyController == NULL)
	{
		return EBTNodeResult::Failed;
	}
	
	AXLAICharacter* MyBot = Cast<AXLAICharacter>(MyController->GetPawn());
	AXLCharacter* Enemy = MyController->GetEnemy();
	if (MyBot)
	{
		int32 Count = MyBot->Nodes.Num();
		for (int32 Position = 0; Position < Count; Position++)
		{
			const FVector Loc = MyBot->Nodes[Position]->GetActorLocation();
			OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), Loc);
			if (Loc != FVector::ZeroVector)
			{
				OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), Loc);
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
