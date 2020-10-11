// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "AI/Tasks/XLSelectNextPatrolPoint.h"
#include "Controllers/XLAIController.h"
#include "Characters/XLAICharacter.h"
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
		for (int32 position = 0; position < Count; position++)
		{
			const FVector Loc = MyBot->Nodes[position]->GetActorLocation();
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
