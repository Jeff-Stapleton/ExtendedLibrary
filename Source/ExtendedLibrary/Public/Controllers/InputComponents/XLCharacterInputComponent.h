// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/InputComponent.h"
#include "Cans/XLControllerCan.h"
#include "XLCharacterInputComponent.generated.h"

class AXLPlayerController;
class APlayerController;
class AXLCharacter;

UCLASS()
class EXTENDEDLIBRARY_API UXLCharacterInputComponent : public UInputComponent
{
	GENERATED_BODY()

public:

	AXLPlayerController* Controller;
	AXLCharacter* Pawn;

public:

	UXLCharacterInputComponent();

	virtual void Init(APlayerController* NewController);

	virtual void ToggleCamera();

	virtual void Move(float Direction);
	virtual void Strafe(float Direction);

	virtual void Turn(float Direction);
	virtual void Look(float Direction);

	virtual void Jump();

	virtual void EquipItem();
	virtual void StowItem();

	virtual void Interact();

	virtual void StartCrouch();
	virtual void StopCrouch();

	virtual void StartSprint();
	virtual void StopSprint();

	virtual void StartActivateItemPrimary();
	virtual void StopActivateItemPrimary();

	virtual void StartActivateItemSecondary();
	virtual void StopActivateItemSecondary();
};
