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

	virtual void Dodge();

	virtual void EquipItem();
	virtual void StowItem();

	virtual void FirstWeapon();
	virtual void SecondWeapon();
	virtual void ThirdWeapon();
	virtual void FourthWeapon();
	virtual void FifthWeapon();
	virtual void SixthWeapon();
	virtual void SeventhWeapon();
	virtual void EighthWeapon();

	virtual void Interact();

	virtual void StartCrouch();
	virtual void StopCrouch();

	virtual void StartProne();
	virtual void StopProne();

	virtual void StartSprint();
	virtual void StopSprint();

	virtual void ActivatePrimary();
	virtual void DeactivatePrimary();

	virtual void ActivateSecondary();
	virtual void DeactivatedSecondary();

	virtual void ActivateTertiary();
	virtual void DeactivateTertiary();

	virtual void Melee();

	virtual void StartAbility1();
	virtual void StopAbility1();

	virtual void StartAbility2();
	virtual void StopAbility2();

	virtual void StartAbility3();
	virtual void StopAbility3();
};
