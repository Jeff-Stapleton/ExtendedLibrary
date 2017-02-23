// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLActionCharacter.h"

AXLActionCharacter::AXLActionCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXLMovementComponent>(ACharacter::CharacterMovementComponentName))

{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 150.0f; 
	CameraBoom->SocketOffset = FVector(0.0f, 50.0f, 50.0f);
	CameraBoom->bUsePawnControlRotation = true; 

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); 
	FollowCamera->bUsePawnControlRotation = false;

}

void AXLActionCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AXLActionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}
