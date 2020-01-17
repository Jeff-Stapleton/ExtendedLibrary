// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLCharacterCan.h"
#include "XLActionCharacter.h"

AXLActionCharacter::AXLActionCharacter(const FObjectInitializer& ObjectInitializer)
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

	PerspectiveMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("PerspectiveMesh"));
	PerspectiveMesh->SetOnlyOwnerSee(true);
	PerspectiveMesh->SetOwnerNoSee(true);
	PerspectiveMesh->bCastDynamicShadow = true;
	PerspectiveMesh->CastShadow = true;
	PerspectiveMesh->RelativeRotation = FRotator(1.9f, -19.19f, 5.2f);
	PerspectiveMesh->RelativeLocation = FVector(-0.5f, -4.4f, -155.7f);
}

void AXLActionCharacter::BeginPlay()
{
	Super::BeginPlay();

	AXLPlayerController* MyPC = Cast<AXLPlayerController>(Controller);
	if (MyPC)
	{
		MyPC->OnTestDelegate.AddDynamic(this, &AXLActionCharacter::ToggleCamera);
	}
}

void AXLActionCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AXLActionCharacter::ToggleCamera()
{
	AXLPlayerController* MyPC = Cast<AXLPlayerController>(Controller);

	if (MyPC->IsFirstPerson)
	{
		GetMesh()->SetOwnerNoSee(true);
		PerspectiveMesh->SetOwnerNoSee(false);
	}
	else
	{
		GetMesh()->SetOwnerNoSee(false);
		PerspectiveMesh->SetOwnerNoSee(true);
	}
}

void AXLActionCharacter::StartAim()
{
	Super::StartAim();
	if (XLCharacterCan::StartAim(this))
	{

	}
}

void AXLActionCharacter::StopAim()
{
	Super::StopAim();
	if (XLCharacterCan::StopAim(this))
	{

	}
}