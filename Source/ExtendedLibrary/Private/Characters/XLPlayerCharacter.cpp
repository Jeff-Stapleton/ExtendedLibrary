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

	Head = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	UpperBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperBody"));
	LowerBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBody"));
	Hands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands"));
	Feet = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));

	Head->SetupAttachment(RootComponent);
	UpperBody->SetupAttachment(RootComponent);
	LowerBody->SetupAttachment(RootComponent);
	Hands->SetupAttachment(RootComponent);
	Feet->SetupAttachment(RootComponent);

	//Ideally we'd adjust the skeletal meshes and not need these
	Head->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Head->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	UpperBody->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	UpperBody->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	LowerBody->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	LowerBody->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	Hands->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Hands->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	Feet->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Feet->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));

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

void AXLPlayerCharacter::StartAim()
{
	Super::StartAim();
	if (XLCharacterCan::StartAim(this))
	{

	}
}

void AXLPlayerCharacter::StopAim()
{
	Super::StopAim();
	if (XLCharacterCan::StopAim(this))
	{

	}
}
