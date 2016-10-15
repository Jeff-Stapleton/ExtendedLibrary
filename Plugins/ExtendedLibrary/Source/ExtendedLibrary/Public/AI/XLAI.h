// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "XLAI.generated.h"

/**
 * 
 */
UCLASS()
class AXLAI : public AXLCharacter
{
	GENERATED_BODY()

public:
	AXLAI();
	
	UPROPERTY(EditAnywhere, Category = Behavior)
	class UBehaviorTree* BotBehavior;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;
};
