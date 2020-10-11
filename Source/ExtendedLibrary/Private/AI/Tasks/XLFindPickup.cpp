// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "AI/Tasks/XLFindPickup.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Controllers/XLAIController.h"
#include "Characters/XLAICharacter.h"
//#include "Pickups/XLPickup_Ammo.h"

UXLFindPickup::UXLFindPickup(const FObjectInitializer& ObjectInitializer) 
	: Super(ObjectInitializer)
{
}

EBTNodeResult::Type UXLFindPickup::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	/*AXLAIController* MyController = Cast<AXLAIController>(OwnerComp.GetAIOwner());
	AXLAICharacter* MyBot = MyController ? Cast<AXLAICharacter>(MyController->GetPawn()) : NULL;
	if (MyBot == NULL)
	{
		return EBTNodeResult::Failed;
	}

	AXLGameMode* GameMode = MyBot->GetWorld()->GetAuthGameMode<AXLGameMode>();
	if (GameMode == NULL)
	{
		return EBTNodeResult::Failed;
	}

	const FVector MyLoc = MyBot->GetActorLocation();
	AXLPickup_Ammo* BestPickup = NULL;
	float BestDistSq = MAX_FLT;

	for (int32 i = 0; i < GameMode->LevelPickups.Num(); ++i)
	{
		AXLPickup_Ammo* AmmoPickup = Cast<AXLPickup_Ammo>(GameMode->LevelPickups[i]);
		if (AmmoPickup && AmmoPickup->IsForWeapon(AXLWeapon_Instant::StaticClass()) && AmmoPickup->CanBePickedUp(MyBot))
		{
			const float DistSq = (AmmoPickup->GetActorLocation() - MyLoc).SizeSquared();
			if (BestDistSq == -1 || DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPickup = AmmoPickup;
			}
		}
	}

	if (BestPickup)
	{
		OwnerComp.GetBlackboardComponent()->SetValue<UBlackboardKeyType_Vector>(BlackboardKey.GetSelectedKeyID(), BestPickup->GetActorLocation());
		return EBTNodeResult::Succeeded;
	}*/

	return EBTNodeResult::Failed;
}
