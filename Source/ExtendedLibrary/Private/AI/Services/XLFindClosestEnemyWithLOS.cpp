// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Controllers/XLAIController.h"
#include "Characters/XLPlayerCharacter.h"
#include "AI/Services/XLFindClosestEnemyWithLOS.h"

UXLFindClosestEnemyWithLOS::UXLFindClosestEnemyWithLOS()
{
	NodeName = "Find Closest Enemy With LOS";
}

void UXLFindClosestEnemyWithLOS::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	//Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	bool bGotEnemy = false;
	AXLAIController* AC = Cast<AXLAIController>(OwnerComp.GetAIOwner());
	APawn* MyBot = Cast<APawn>(AC->GetPawn());
	if (MyBot != NULL)
	{
		const FVector MyLoc = MyBot->GetActorLocation();
		float BestDistSq = 10000000.0f;//AgroDistance;
		AXLCharacter* BestPawn = NULL;

		for (TActorIterator<AXLPlayerCharacter> It = TActorIterator<AXLPlayerCharacter>(GetWorld()); It; ++It)
		{
			AXLPlayerCharacter* TestPawn = Cast<AXLPlayerCharacter>(*It);
			if (TestPawn /*&& TestPawn != ExcludeEnemy*/ && TestPawn->HealthState == EHealthState::Alive /*&& TestPawn->IsEnemyFor(this)*/)
			{
				const float DistSq = (TestPawn->GetActorLocation() - MyLoc).SizeSquared();
				if (DistSq < BestDistSq)
				{
					BestDistSq = DistSq;
					BestPawn = TestPawn;
				}
			}
		}
		if (BestPawn)
		{
			AC->SetEnemy(BestPawn);
			bGotEnemy = true;
		}
	}
}
