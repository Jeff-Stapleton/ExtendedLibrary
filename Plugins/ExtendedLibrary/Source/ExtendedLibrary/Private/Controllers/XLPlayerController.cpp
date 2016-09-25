// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPlayerController.h"

AXLPlayerController::AXLPlayerController()
{
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
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

void AXLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAxis("Move", this, &AXLPlayerController::Move);
	InputComponent->BindAxis("Strafe", this, &AXLPlayerController::Strafe);

	InputComponent->BindAxis("Turn", this, &AXLPlayerController::Turn);
	InputComponent->BindAxis("Look", this, &AXLPlayerController::Look);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AXLPlayerController::Jump);

	InputComponent->BindAction("Dodge", IE_Pressed, this, &AXLPlayerController::Dodge);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AXLPlayerController::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AXLPlayerController::StopSprint);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AXLPlayerController::StartAttack);
	InputComponent->BindAction("Attack", IE_Released, this, &AXLPlayerController::StopAttack);

	InputComponent->BindAction("Reload", IE_Pressed, this, &AXLPlayerController::Reload);

	InputComponent->BindAction("Melee", IE_Pressed, this, &AXLPlayerController::Melee);

	InputComponent->BindAction("Special", IE_Pressed, this, &AXLPlayerController::StartSpecial);
	InputComponent->BindAction("Special", IE_Released, this, &AXLPlayerController::StopSpecial);

	InputComponent->BindAction("Primary Ability", IE_Pressed, this, &AXLPlayerController::StartPrimaryAbility);
	InputComponent->BindAction("Primary Ability", IE_Released, this, &AXLPlayerController::StopPrimaryAbility);

	InputComponent->BindAction("Secondary Ability", IE_Pressed, this, &AXLPlayerController::StartSecondaryAbility);
	InputComponent->BindAction("Secondary Ability", IE_Released, this, &AXLPlayerController::StopSecondaryAbility);

	InputComponent->BindAction("Ultimate", IE_Pressed, this, &AXLPlayerController::StartUltimate);
	InputComponent->BindAction("Ultimate", IE_Released, this, &AXLPlayerController::StartUltimate);
}

void AXLPlayerController::Move(float Direction)
{
	
}

void AXLPlayerController::Strafe(float Direction)
{

}

void AXLPlayerController::Turn(float Direction)
{
	
}

void AXLPlayerController::Look(float Direction)
{

}

void AXLPlayerController::Jump()
{
	
}

void AXLPlayerController::Dodge()
{
	
}

void AXLPlayerController::StartSprint()
{
	
}

void AXLPlayerController::StopSprint()
{
	
}

void AXLPlayerController::StartAttack()
{
	
}

void AXLPlayerController::StopAttack()
{
	
}

void AXLPlayerController::Reload()
{
	
}

void AXLPlayerController::Melee()
{
	
}

void AXLPlayerController::StartSpecial()
{
	
}

void AXLPlayerController::StopSpecial()
{
	
}

void AXLPlayerController::StartPrimaryAbility()
{
	
}

void AXLPlayerController::StopPrimaryAbility()
{
	
}

void AXLPlayerController::StartSecondaryAbility()
{
	
}

void AXLPlayerController::StopSecondaryAbility()
{
	
}

void AXLPlayerController::StartUltimate()
{
	
}

void AXLPlayerController::StopUltimate()
{
	
}

void AXLPlayerController::UnFreeze()
{
	ServerRestartPlayer();
}

void AXLPlayerController::Reset()
{
	Super::Reset();
}




