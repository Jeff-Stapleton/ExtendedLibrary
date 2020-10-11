// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Engine/InputDelegateBinding.h"
#include "Managers/XLPlayerCameraManager.h"
#include "Controllers/InputComponents/XLCharacterInputComponent.h"
#include "Controllers/XLPlayerController.h"

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

	FInputModeGameOnly inputMode;
	SetInputMode(inputMode);
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

	if (UInputDelegateBinding::SupportsInputDelegate(GetClass()))
	{
		UInputDelegateBinding::BindInputDelegates(GetClass(), CharacterInputComponent);
	}

	SetControllerInputMode(InputMode);
}

void AXLPlayerController::SetControllerInputMode(TEnumAsByte<EInputMode::Type> Mode)
{
	ResetInputMode();
	switch (Mode) 
	{
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
}

void AXLPlayerController::UnFreeze()
{
	ServerRestartPlayer();
}

void AXLPlayerController::Reset()
{
	Super::Reset();
}




