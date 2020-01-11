// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/InputComponent.h"
#include "Controllers/XLPlayerController.h"
#include "XLAirVehicleInputComponent.generated.h"

UCLASS()
class UXLAirVehicleInputComponent : public UInputComponent
{
	GENERATED_BODY()

	UXLAirVehicleInputComponent();

public:

	AXLPlayerController* Controller;
	AXLAirVehicle* Pawn;

public:

	void Init(AXLPlayerController* NewController);

	virtual void TakeOff();

	virtual void Accelerate(float Value);

	virtual void Pitch(float Value);
	virtual void Yaw(float Value);
	virtual void Roll(float Value);

	virtual void Strafe(float Value);
};
