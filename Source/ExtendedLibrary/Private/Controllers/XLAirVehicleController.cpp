// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAirVehicleController.h"

AXLAirVehicleController::AXLAirVehicleController()
{
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AXLAirVehicleController::BeginPlay()
{
	Super::BeginPlay();
}

void AXLAirVehicleController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AXLAirVehicleController::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AXLAirVehicleController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

}


void AXLAirVehicleController::UnFreeze()
{
	ServerRestartPlayer();
}

void AXLAirVehicleController::Reset()
{
	Super::Reset();
}




