// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "XLAirVehicle.h"

AXLAirVehicle::AXLAirVehicle(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXLAirVehicleMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 2500.0f; 	
	SpringArm->SocketOffset = FVector(0.0f, 0.0f, 250.0f);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);

	MeshCenterOfMass = CreateDefaultSubobject<UCapsuleComponent>(TEXT("MeshCapsule"));
	MeshCenterOfMass->SetupAttachment(RootComponent);
	GetMesh()->SetupAttachment(MeshCenterOfMass);

	bUseControllerRotationYaw = true;
	bUseControllerRotationPitch = true;
	bUseControllerRotationRoll = true;

	MovementComponent = Cast<UXLAirVehicleMovementComponent>(GetMovementComponent());
}

void AXLAirVehicle::BeginPlay()
{
	Super::BeginPlay();

	MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
}

void AXLAirVehicle::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (IsLanded == false)
	{
		Move(DeltaSeconds);
		RotateController(DeltaSeconds);
		RotateMesh(DeltaSeconds);
		//Stabilize();
	}
}

void AXLAirVehicle::TakeOff()
{
	if (IsLanded)
	{
		IsLanded = false;
		MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
	}
	else
	{
		IsLanded = true;
		MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
	}
}

void AXLAirVehicle::Move(float DeltaSeconds)
{
	if (XLAirVehicleCan::Move(this))
	{
		MovementComponent->MaxFlySpeed = FMath::FInterpTo(MovementComponent->MaxFlySpeed, MovementComponent->TargetSpeed, DeltaSeconds, 0.2);
		AddMovementInput(Controller->GetControlRotation().Vector());
	}
}

void AXLAirVehicle::RotateController(float DeltaSeconds)
{
	if (XLAirVehicleCan::Rotate(this))
	{
		MovementComponent->ControllerCurrentPitch = FMath::FInterpTo(MovementComponent->ControllerCurrentPitch, MovementComponent->ControllerTargetPitch, DeltaSeconds, MovementComponent->PitchResponsiveness);
		MovementComponent->ControllerCurrentYaw = FMath::FInterpTo(MovementComponent->ControllerCurrentYaw, MovementComponent->ControllerTargetYaw, DeltaSeconds, MovementComponent->YawResponsiveness);
		MovementComponent->ControllerCurrentRoll = FMath::FInterpTo(MovementComponent->ControllerCurrentRoll, MovementComponent->ControllerTargetRoll, DeltaSeconds, MovementComponent->RollResponsiveness);

		FRotator Rotation = FRotator(MovementComponent->ControllerCurrentPitch, MovementComponent->ControllerCurrentYaw, MovementComponent->ControllerCurrentRoll);
		GetController()->SetControlRotation(Rotation);
	}
}

void AXLAirVehicle::RotateMesh(float DeltaSeconds)
{
	if (XLAirVehicleCan::Rotate(this))
	{
		MovementComponent->MeshCurrentPitch = FMath::FInterpTo(MovementComponent->MeshCurrentPitch, MovementComponent->MeshTargetPitch, DeltaSeconds, MovementComponent->PitchResponsiveness);
		MovementComponent->MeshCurrentYaw = FMath::FInterpTo(MovementComponent->MeshCurrentYaw, MovementComponent->MeshTargetYaw, DeltaSeconds, MovementComponent->YawResponsiveness);
		MovementComponent->MeshCurrentRoll = FMath::FInterpTo(MovementComponent->MeshCurrentRoll, MovementComponent->MeshTargetRoll, DeltaSeconds, MovementComponent->RollResponsiveness);

		FRotator Rotation = FRotator(MovementComponent->MeshCurrentPitch, MovementComponent->MeshCurrentYaw, MovementComponent->MeshCurrentRoll);
		MeshCenterOfMass->SetRelativeRotation(Rotation);
	}
}

void AXLAirVehicle::Stabilize()
{
	if (XLAirVehicleCan::Stabilize(this))
	{
		FRotator CurrentRotation = GetActorRotation();
		FRotator TargetRotation = FRotator(CurrentRotation.Pitch, CurrentRotation.Yaw, 0);
		SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), TargetRotation.Quaternion(), MovementComponent->StabilizeRate));

		if (MovementComponent->IsRolling == false)
		{
			FRotator ControllerCurrentRollRotation = MeshCenterOfMass->RelativeRotation;
			FRotator ControllerTargetRollRotation = FRotator(MeshCenterOfMass->RelativeRotation.Pitch, MeshCenterOfMass->RelativeRotation.Yaw, 0);
			MeshCenterOfMass->SetRelativeRotation(FQuat::Slerp(ControllerCurrentRollRotation.Quaternion(), ControllerTargetRollRotation.Quaternion(), MovementComponent->StabilizeRate));
		}
	}
}

void AXLAirVehicle::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Deflect along the surface when we collide.
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}

void AXLAirVehicle::Accelerate(float Value)
{
	if (XLAirVehicleCan::Accelerate(this))
	{
		MovementComponent->TargetSpeed += MovementComponent->GetMaxAcceleration() * Value * GetWorld()->GetDeltaSeconds();
		if (MovementComponent->TargetSpeed > MovementComponent->DefaultSpeed)
		{
			MovementComponent->TargetSpeed = MovementComponent->DefaultSpeed;
		}
		if (MovementComponent->TargetSpeed < MovementComponent->MinSpeed)
		{
			MovementComponent->TargetSpeed = MovementComponent->MinSpeed;
		}
		MovementComponent->MaxFlySpeed = MovementComponent->TargetSpeed;
	}
}

void AXLAirVehicle::Pitch(float Value)
{
	if (XLAirVehicleCan::Pitch(this) && Value != 0)
	{
		float Input = FMath::Clamp(Value, -1.0f, 1.0f);

		MovementComponent->ControllerTargetPitch = MovementComponent->ControllerCurrentPitch + (Input * MovementComponent->PitchSpeed);
	}
}

void AXLAirVehicle::Yaw(float Value)
{
	if (XLAirVehicleCan::Yaw(this) && Value != 0)
	{
		float Input = FMath::Clamp(Value, -1.0f, 1.0f);

		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Roll %f"), temp));
		MovementComponent->ControllerTargetRoll = MovementComponent->RollWhileTurning * Input;
		MovementComponent->ControllerTargetYaw = MovementComponent->ControllerCurrentYaw + (Input * MovementComponent->YawSpeed);
	}
}

void AXLAirVehicle::Roll(float Value)
{
	if (MovementComponent)
	{
		if (XLAirVehicleCan::Roll(this) && Value != 0)
		{
			MovementComponent->IsRolling = true;
			MovementComponent->MeshTargetRoll = MovementComponent->MeshCurrentRoll + (Value * MovementComponent->RollSpeed);
		}
		else
		{
			MovementComponent->IsRolling = false;
		}
	}
}

void AXLAirVehicle::Strafe(float Value)
{
	if (XLAirVehicleCan::Strafe(this) && Value != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		MovementComponent->MeshTargetRoll = MovementComponent->RollWhileStrafing * Value;
		AddMovementInput(Direction, Value);
	}
}

void AXLAirVehicle::OnInspect_Implementation(AActor* Instigator)
{

}

void AXLAirVehicle::OnInteract_Implementation(AActor* Instigator)
{
	Instigator->GetInstigatorController()->Possess(this);
	Instigator->Destroy();

	(Cast<AXLPlayerController>(Controller))->SetControllerInputMode(EInputMode::AirVehicle);
}