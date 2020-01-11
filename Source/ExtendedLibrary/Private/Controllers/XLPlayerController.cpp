// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Engine/InputDelegateBinding.h"
#include "XLPlayerController.h"

AXLPlayerController::AXLPlayerController()
{
	PlayerCameraManagerClass = AXLPlayerCameraManager::StaticClass();

	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	InputMode = EInputMode::Character;
}

void AXLPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AXLPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AXLPlayerController::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AXLPlayerController::TogglePerspective()
{
	if (IsFirstPerson)
	{
		IsFirstPerson = false;
	}
	else
	{
		IsFirstPerson = true;
	}
	OnTestDelegate.Broadcast();
}

void AXLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	ResetInputMode();

	CharacterInputComponent = NewObject<UXLCharacterInputComponent>(this);
	CharacterInputComponent->Init(this);

	AirVehicleInputComponent = NewObject<UXLAirVehicleInputComponent>(this);
	AirVehicleInputComponent->Init(this);

	if (UInputDelegateBinding::SupportsInputDelegate(GetClass()))
	{
		UInputDelegateBinding::BindInputDelegates(GetClass(), CharacterInputComponent);
		UInputDelegateBinding::BindInputDelegates(GetClass(), AirVehicleInputComponent);
	}

	SetControllerInputMode(InputMode);
}

void AXLPlayerController::SetControllerInputMode(TEnumAsByte<EInputMode::Type> Mode)
{
	ResetInputMode();
	switch (Mode) 
	{
		case EInputMode::AirVehicle:
			PushInputComponent(AirVehicleInputComponent);
			break;
		case EInputMode::Character:
			PushInputComponent(CharacterInputComponent);
			break;
		default:
			PushInputComponent(CharacterInputComponent);
			break;
	}
}

void AXLPlayerController::ResetInputMode()
{
	PopInputComponent(InputComponent);
	PopInputComponent(CharacterInputComponent);
	PopInputComponent(AirVehicleInputComponent);
}

void AXLPlayerController::UnFreeze()
{
	ServerRestartPlayer();
}

void AXLPlayerController::Reset()
{
	Super::Reset();
}




