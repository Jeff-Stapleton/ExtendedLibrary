// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "XLCharacter.h"
#include "XLAICharacter.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLAICharacter : public AXLCharacter
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, Category=Behavior)
	class UBehaviorTree* BotBehavior;

	//virtual bool IsFirstPerson() const override;

	virtual void FaceRotation(FRotator NewRotation, float DeltaTime = 0.f) override;

	UPROPERTY(EditAnywhere, Category = Config)
	TArray<class ATargetPoint*> Nodes;
};