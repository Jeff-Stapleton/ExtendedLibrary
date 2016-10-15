// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

AXLAIController::AXLAIController()
{
	BlackboardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComp"));

	BehaviorComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComp"));

	bWantsPlayerState = true;
}

void AXLAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AXLAI* Bot = Cast<AXLAI>(InPawn);

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

	AGameState* GameState = GetWorld()->GameState;

	const float MinRespawnDelay = (GameState && GameState->GameModeClass) ? GetDefault<AGameMode>(GameState->GameModeClass)->MinRespawnDelay : 1.0f;

	GetWorldTimerManager().SetTimer(TimerHandle_Respawn, this, &AXLAIController::Respawn, MinRespawnDelay);
}

void AXLAIController::Respawn()
{
	GetWorld()->GetAuthGameMode()->RestartPlayer(this);
}

void AXLAIController::FindClosestEnemy()
{
	APawn* MyBot = GetPawn();
	if (MyBot == NULL)
	{
		return;
	}

	const FVector MyLoc = MyBot->GetActorLocation();
	float BestDistSq = 3000000.0f; //agro distance
	AXLPlayerCharacter* BestPawn = NULL;

	for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
	{
		AXLPlayerCharacter* TestPawn = Cast<AXLPlayerCharacter>(*It);
		if (TestPawn && TestPawn->HealthState == EHealthState::Alive /*&& TestPawn->IsEnemyFor(this)*/)
		{
			const float DistSq = (TestPawn->GetActorLocation() - MyLoc).SizeSquared();
			if (DistSq < BestDistSq)
			{
				BestDistSq = DistSq;
				BestPawn = TestPawn;
			}
		}
	}
	SetEnemy(BestPawn);
}

bool AXLAIController::FindClosestEnemyWithLOS(AXLPlayerCharacter* ExcludeEnemy)
{
	bool bGotEnemy = false;
	APawn* MyBot = GetPawn();
	if (MyBot != NULL)
	{
		const FVector MyLoc = MyBot->GetActorLocation();
		float BestDistSq = 3000000.0f; //agro distance
		AXLPlayerCharacter* BestPawn = NULL;

		for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; ++It)
		{
			AXLPlayerCharacter* TestPawn = Cast<AXLPlayerCharacter>(*It);
			if (TestPawn && TestPawn != ExcludeEnemy && TestPawn->HealthState == EHealthState::Alive /*&& TestPawn->IsEnemyFor(this)*/)
			{
				if (HasWeaponLOSToEnemy(TestPawn, true) == true)
				{
					const float DistSq = (TestPawn->GetActorLocation() - MyLoc).SizeSquared();
					if (DistSq < BestDistSq)
					{
						BestDistSq = DistSq;
						BestPawn = TestPawn;
					}
				}
			}
		}
		if (BestPawn)
		{
			SetEnemy(BestPawn);
			bGotEnemy = true;
		}
		SetEnemy(BestPawn);
	}
	return bGotEnemy;
}

bool AXLAIController::HasWeaponLOSToEnemy(AActor* InEnemyActor, const bool bAnyEnemy) const
{
	static FName LosTag = FName(TEXT("AIWeaponLosTrace"));

	AXLAI* MyBot = Cast<AXLAI>(GetPawn());

	bool bHasLOS = false;
	// Perform trace to retrieve hit info
	FCollisionQueryParams TraceParams(LosTag, true, GetPawn());
	TraceParams.bTraceAsyncScene = true;

	TraceParams.bReturnPhysicalMaterial = true;
	FVector StartLocation = MyBot->GetActorLocation();
	StartLocation.Z += GetPawn()->BaseEyeHeight; //look from eyes

	FHitResult Hit(ForceInit);
	const FVector EndLocation = InEnemyActor->GetActorLocation();
	GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, COLLISION_WEAPON, TraceParams);
	if (Hit.bBlockingHit == true)
	{
		// Theres a blocking hit - check if its our enemy actor
		AActor* HitActor = Hit.GetActor();
		if (Hit.GetActor() != NULL)
		{
			if (HitActor == InEnemyActor)
			{
				bHasLOS = true;
			}
			else if (bAnyEnemy == true)
			{
				// Its not our actor, maybe its still an enemy ?
				ACharacter* HitChar = Cast<ACharacter>(HitActor);
				if (HitChar != NULL)
				{
					AXLPlayerState* HitPlayerState = Cast<AXLPlayerState>(HitChar->PlayerState);
					AXLPlayerState* MyPlayerState = Cast<AXLPlayerState>(PlayerState);
					if ((HitPlayerState != NULL) && (MyPlayerState != NULL))
					{
						if (HitPlayerState->GetTeamNum() != MyPlayerState->GetTeamNum())
						{
							bHasLOS = true;
						}
					}
				}
			}
		}
	}



	return bHasLOS;
}

void AXLAIController::ShootEnemy()
{
	/*AXLAI* MyBot = Cast<AXLAI>(GetPawn());
	AXLWeapon* MyWeapon = MyBot ? MyBot->CharacterWeapon : NULL;
	if (SSWeaponCan::Attack(MyWeapon))
	{
		bool bCanShoot = false;
		AXLPlayerCharacter* Enemy = GetEnemy();
		if (Enemy && (Enemy->IsAlive()) && (SSWeaponCan::Attack(MyWeapon) == true))
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
	}*/
}

void AXLAIController::CheckAmmo(const class AXLWeapon* CurrentWeapon)
{
	if (CurrentWeapon && BlackboardComp)
	{
		BlackboardComp->SetValue<UBlackboardKeyType_Bool>(NeedAmmoKeyID, false);
	}
}

void AXLAIController::SetEnemy(class APawn* InPawn)
{
	if (InPawn)
	{
		if (BlackboardComp)
		{
			BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
			SetFocus(InPawn);
		}
	}
	else
	{
		BlackboardComp->ClearValue(EnemyKeyID);
		SetFocus(InPawn);
	}
}

class AXLPlayerCharacter* AXLAIController::GetEnemy() const
{
	if (BlackboardComp)
	{
		return Cast<AXLPlayerCharacter>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	}

	return NULL;
}

void AXLAIController::UpdateControlRotation(float DeltaTime, bool bUpdatePawn)
{
	// Look toward focus
	FVector FocalPoint = GetFocalPoint();
	if (!FocalPoint.IsZero() && GetPawn())
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

void AXLAIController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	// Stop the behaviour tree/logic
	BehaviorComp->StopTree();

	// Stop any movement we already have
	StopMovement();

	// Cancel the repsawn timer
	GetWorldTimerManager().ClearTimer(TimerHandle_Respawn);

	// Clear any enemy
	SetEnemy(NULL);

	// Finally stop firing
	AXLAI* MyBot = Cast<AXLAI>(GetPawn());
	//AXLWeapon* MyWeapon = MyBot ? MyBot->CharacterWeapon : NULL;
	//if (MyWeapon == NULL)
	//{
	//	return;
	//}
	MyBot->StopAttack();
}





