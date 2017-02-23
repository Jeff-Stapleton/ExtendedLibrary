// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once
#include "AIController.h"
#include "XLAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS(config=Game)
class AXLAIController : public AAIController
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(transient)
	UBlackboardComponent* BlackboardComp;

	UPROPERTY(transient)
	UBehaviorTreeComponent* BehaviorComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Agro)
	float AgroDistance = 5000000.0f;

public:

	virtual void Possess(class APawn* InPawn) override;
	virtual void UnPossess() override;
	virtual void BeginInactiveState() override;

	void Respawn();

	void SetEnemy(class APawn* InPawn);

	class AXLCharacter* GetEnemy() const;

	virtual void UpdateControlRotation(float DeltaTime, bool bUpdatePawn = true) override;

protected:

	bool LOSTrace(AXLCharacter* InEnemyChar) const;

	int32 EnemyKeyID;
	int32 NeedAmmoKeyID;

	/** Handle for efficient management of Respawn timer */
	FTimerHandle TimerHandle_Respawn;

public:
	/** Returns BlackboardComp subobject **/
	FORCEINLINE UBlackboardComponent* GetBlackboardComp() const { return BlackboardComp; }
	/** Returns BehaviorComp subobject **/
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorComp() const { return BehaviorComp; }
};
