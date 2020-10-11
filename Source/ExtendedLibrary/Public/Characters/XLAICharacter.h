// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "Characters/XLCharacter.h"
#include "XLAICharacter.generated.h"

class UBehaviorTree;
class ATargetPoint;

UCLASS()
class EXTENDEDLIBRARY_API AXLAICharacter : public AXLCharacter
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, Category=Behavior)
	UBehaviorTree* BotBehavior;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

	UPROPERTY(EditAnywhere, Category = Config)
	TArray<ATargetPoint*> Nodes;
};
