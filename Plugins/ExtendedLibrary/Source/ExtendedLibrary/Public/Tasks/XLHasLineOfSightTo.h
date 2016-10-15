// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "XLHasLineOfSightTo.generated.h"

/**
 * 
 */
UCLASS()
class UXLHasLineOfSightTo : public UBTDecorator
{
	GENERATED_BODY()

public:

	UXLHasLineOfSightTo();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

protected:

	UPROPERTY(EditAnywhere, Category = Condition)
	struct FBlackboardKeySelector EnemyKey;

private:

	bool LOSTrace(AActor* InActor, AActor* InEnemyActor, const FVector& EndLocation) const;
};
