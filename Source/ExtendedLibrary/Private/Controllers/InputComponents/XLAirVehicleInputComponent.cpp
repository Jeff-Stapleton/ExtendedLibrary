// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAirVehicleInputComponent.h"

UXLAirVehicleInputComponent::UXLAirVehicleInputComponent()
{
}

void UXLAirVehicleInputComponent::Init(AXLPlayerController* NewController)
{
	RegisterComponent();
	bBlockInput = false;
	Priority = 0;

	Controller = NewController;

	//InputComponent->BindAxis("MoveVertical", this, &AXLAirVehicleController::Look);
	//InputComponent->BindAxis("MoveHorizontal", this, &AXLAirVehicleController::Strafe);

	BindAction("TakeOff", IE_Pressed, this, &UXLAirVehicleInputComponent::TakeOff);

	BindAxis("Accelerate", this, &UXLAirVehicleInputComponent::Accelerate);

	BindAxis("Pitch", this, &UXLAirVehicleInputComponent::Pitch);
	BindAxis("Yaw", this, &UXLAirVehicleInputComponent::Yaw);
	BindAxis("Roll", this, &UXLAirVehicleInputComponent::Roll);

	BindAxis("Strafe", this, &UXLAirVehicleInputComponent::Strafe);

	//InputComponent->BindAction("Attack", IE_Pressed, this, &AXLAirVehicleController::StartAttack);
	//InputComponent->BindAction("Attack", IE_Released, this, &AXLAirVehicleController::StopAttack);
}

void UXLAirVehicleInputComponent::TakeOff()
{
	if (this && Cast<AXLAirVehicle>(Controller->GetPawn()))
	{
		(Cast<AXLAirVehicle>(Controller->GetPawn()))->TakeOff();
	}
}

void UXLAirVehicleInputComponent::Accelerate(float Value)
{
	// if (XLControllerCan::Move(this))
	if (this && Cast<AXLAirVehicle>(Controller->GetPawn()))
	{
		(Cast<AXLAirVehicle>(Controller->GetPawn()))->Accelerate(Value);
	}
}

void UXLAirVehicleInputComponent::Pitch(float Value)
{
	// if (XLControllerCan::Move(this))
	if (this && Cast<AXLAirVehicle>(Controller->GetPawn()))
	{
		(Cast<AXLAirVehicle>(Controller->GetPawn()))->Pitch(Value);
	}
}

void UXLAirVehicleInputComponent::Yaw(float Value)
{
	// if (XLControllerCan::Move(this))
	if (this && Cast<AXLAirVehicle>(Controller->GetPawn()))
	{
		(Cast<AXLAirVehicle>(Controller->GetPawn()))->Yaw(Value);
	}
}

void UXLAirVehicleInputComponent::Roll(float Value)
{
	if (this && Cast<AXLAirVehicle>(Controller->GetPawn()))
	{
		(Cast<AXLAirVehicle>(Controller->GetPawn()))->Roll(Value);
	}
}

void UXLAirVehicleInputComponent::Strafe(float Value)
{
	// if (XLControllerCan::Move(this))
	if (this && Cast<AXLAirVehicle>(Controller->GetPawn()))
	{
		(Cast<AXLAirVehicle>(Controller->GetPawn()))->Strafe(Value);
	}
}