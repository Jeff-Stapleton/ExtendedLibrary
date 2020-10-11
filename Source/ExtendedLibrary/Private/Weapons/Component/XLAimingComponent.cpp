#include "ExtendedLibraryPCH.h"
#include "Characters/XLPlayerCharacter.h"
#include "Camera/XLCamera.h"
#include "Weapons/Components/XLAimingComponent.h"

UXLAimingComponent::UXLAimingComponent()
{
	bWantsInitializeComponent = true;
}

void UXLAimingComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Owner = Cast<AXLItem>(GetOwner());
}

FVector UXLAimingComponent::GetAdjustedAim()
{
	const FVector Origin = GetAimOrigin();
	const FVector Destination = GetAimDestination();

	FVector Target = Origin + Destination * 10000.0f;

	return Trace(Origin, Target);
}

FVector UXLAimingComponent::GetAimOrigin()
{
	AXLPlayerController* PC = Owner->Character ? Cast<AXLPlayerController>(Owner->Character->Controller) : NULL;
	AXLAIController* AIPC = Owner->Character ? Cast<AXLAIController>(Owner->Character->Controller) : NULL;

	FVector Origin = FVector::ZeroVector;
	if (PC)
	{
		Origin = Cast<AXLPlayerCharacter>(Owner->Character)->Camera->GetComponentLocation();
	}
	if (AIPC)
	{
		Origin = Owner->GetSocketLocation("Muzzle");
	}

	return Origin;
}

FVector UXLAimingComponent::GetAimDestination()
{
	AXLPlayerController* PC = Owner->Character ? Cast<AXLPlayerController>(Owner->Character->Controller) : NULL;
	AXLAIController* AIPC = Owner->Character ? Cast<AXLAIController>(Owner->Character->Controller) : NULL;

	FRandomStream WeaponRandomStream(FMath::Rand());
	const float ConeHalfAngle = FMath::DegreesToRadians(1.0f * 0.0f);

	FVector AimDir = FVector::ZeroVector;
	if (PC)
	{
		AimDir = Cast<AXLPlayerCharacter>(Owner->Character)->Camera->GetForwardVector();
	}
	if (AIPC)
	{
		AimDir = AIPC->GetControlRotation().Vector();
	}
	return WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
}

FVector UXLAimingComponent::Trace(FVector Origin, FVector Target)
{
	FCollisionQueryParams TraceParams(SCENE_QUERY_STAT(PreTrace), true, Owner->Character);
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	Owner->GetWorld()->LineTraceSingleByChannel(Hit, Origin, Target, COLLISION_PROJECTILE, TraceParams);
	//Owner->GetWorld()->DebugDrawTraceTag = PreTraceTag;

	return Hit.bBlockingHit ? Hit.ImpactPoint : Hit.TraceEnd;
}
