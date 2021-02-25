// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Characters/XLPlayerCharacter.h"
#include "Cans/XLCharacterCan.h"
#include "Components/Character/XLMovementComponent.h"
#include "Camera/XLCamera.h"

AXLPlayerCharacter::AXLPlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXLMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150.0f;
	CameraBoom->SocketOffset = FVector(0.0f, 50.0f, 50.0f);
	CameraBoom->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UXLCamera>(TEXT("Camera"));
	Camera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
}

void AXLPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	AXLPlayerController* MyPC = Cast<AXLPlayerController>(Controller);
	if (MyPC)
	{
		MyPC->OnTestDelegate.AddDynamic(this, &AXLPlayerCharacter::ToggleCamera);
	}
}

void AXLPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AXLPlayerCharacter::ToggleCamera()
{
	AXLPlayerController* MyPC = Cast<AXLPlayerController>(Controller);

	if (MyPC->IsFirstPerson)
	{
		//GetMesh()->SetOwnerNoSee(true);
	}
	else
	{
		//GetMesh()->SetOwnerNoSee(false);
	}
}
