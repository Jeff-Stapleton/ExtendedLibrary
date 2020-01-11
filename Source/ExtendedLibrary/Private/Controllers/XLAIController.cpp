// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "XLAIController.h"
#include "XLAICharacter.h"
#include "XLActionCharacter.h"
#include "XLHealthState.h"
#include "Online/XLPlayerState.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "XLWeapon.h"

AXLAIController::AXLAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	BlackboardComp = ObjectInitializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackBoardComp"));
	BrainComponent = BehaviorComp = ObjectInitializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));	

	bWantsPlayerState = true;
}

void AXLAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AXLAICharacter* Bot = Cast<AXLAICharacter>(InPawn);

	// start behavior
	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			BlackboardComp->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}

		EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
		NeedAmmoKeyID = BlackboardComp->GetKeyID("NeedAmmo");

		BehaviorComp->StartTree(*(Bot->BotBehavior));
	}
}

void AXLAIController::UnPossess()
{
	Super::UnPossess();

	BehaviorComp->StopTree();
}

void AXLAIController::BeginInactiveState()
{
	Super::BeginInactiveState();

	AGameStateBase const* const GameState = GetWorld()->GetGameState();

	const float MinRespawnDelay = GameState ? GameState->GetPlayerRespawnDelay(this) : 1.0f;

	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &AXLAIController::Respawn, MinRespawnDelay);
}

void AXLAIController::Respawn()
{
	//GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

void AXLAIController::ShootEnemy()
{
	AXLAICharacter* MyBot = Cast<AXLAICharacter>(GetPawn());
	AXLItem* MyWeapon = MyBot ? MyBot->CharacterInventory->GetItem(MyBot->CurrentItem) : NULL;
	if (MyWeapon == NULL)
	{
		return;
	}

	bool bCanShoot = false;
	AXLCharacter* Enemy = GetEnemy();
	if (Enemy /*&& is enemy alive && can I shoot*/)
	{
		if (LineOfSightTo(Enemy, MyBot->GetActorLocation()))
		{
			bCanShoot = true;
		}
	}

	if (bCanShoot)
	{
		MyBot->StartAttack();
	}
	else
	{
		MyBot->StopAttack();
	}
}

void AXLAIController::StopAttacking()
{
	AXLAICharacter* MyBot = Cast<AXLAICharacter>(GetPawn());
	if (MyBot)
	{
		MyBot->StopAttack();
	}
	else
	{
		return;
	}
}


void AXLAIController::SetEnemy(class APawn* InPawn)
{
	if (BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
		SetFocus(InPawn);
	}
}

class AXLCharacter* AXLAIController::GetEnemy() const
{
	if (BlackboardComp)
	{
		return Cast<AXLCharacter>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}

	return NULL;
}


void AXLAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	// Look toward focus
	FVector FocalPoint = GetFocalPoint();
	if( !FocalPoint.IsZero() && GetPawn())
	{
		FVector Direction = FocalPoint - GetPawn()->GetActorLocation();
		FRotator NewControlRotation = Direction.Rotation();
		
		NewControlRotation.Yaw = FRotator::ClampAxis(NewControlRotation.Yaw);

		SetControlRotation(NewControlRotation);

		APawn* const P = GetPawn();
		if (P && bUpdatePawn)
		{
			P->FaceRotation(NewControlRotation, DeltaTime);
		}
		
	}
}
