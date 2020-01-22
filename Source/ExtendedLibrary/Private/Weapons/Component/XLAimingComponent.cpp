#include "ExtendedLibraryPCH.h"
#include "XLAimingComponent.h"

UXLAimingComponent::UXLAimingComponent()
{
	bWantsInitializeComponent = true;
}


void UXLAimingComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Owner = Cast<AXLRangedWeapon>(GetOwner());
}

FVector UXLAimingComponent::GetAdjustedAim()
{
	const FVector Origin = GetAimOrigin();
	const FVector Destination = GetAimDestination();

	FVector Target = Origin + Destination * MaxRange;

	return Trace(Origin, Target);
}

FVector UXLAimingComponent::GetAimDestination()
{
	AXLPlayerController* PC = Owner->Character ? Cast<AXLPlayerController>(Owner->Character->Controller) : NULL;
	AXLAIController* AIPC = Owner->Character ? Cast<AXLAIController>(Owner->Character->Controller) : NULL;

	FRandomStream WeaponRandomStream(FMath::Rand());
	const float ConeHalfAngle = FMath::DegreesToRadians(Bloom * 0.5f);

	FVector AimDir = FVector::ZeroVector;
	if (PC)
	{
		AimDir = Cast<AXLActionCharacter>(Owner->Character)->Camera->GetForwardVector();
	}
	if (AIPC)
	{
		AimDir = AIPC->GetControlRotation().Vector();
	}
	return WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
}

FVector UXLAimingComponent::GetAimOrigin()
{
	AXLPlayerController* PC = Owner->Character ? Cast<AXLPlayerController>(Owner->Character->Controller) : NULL;
	AXLAIController* AIPC = Owner->Character ? Cast<AXLAIController>(Owner->Character->Controller) : NULL;

	FVector Origin = FVector::ZeroVector;
	if (PC)
	{
		Origin = Cast<AXLActionCharacter>(Owner->Character)->Camera->GetComponentLocation();
	}
	if (AIPC)
	{
		Origin = Owner->GetMuzzleLocation();
	}

	return Origin;
}

FVector UXLAimingComponent::Trace(FVector Origin, FVector Target)
{
	static FName PreTraceTag = FName(TEXT("PreTrace"));
	FCollisionQueryParams TraceParams(PreTraceTag, true, Owner->Character);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	Owner->GetWorld()->LineTraceSingleByChannel(Hit, Origin, Target, COLLISION_PROJECTILE, TraceParams);
	//Owner->GetWorld()->DebugDrawTraceTag = PreTraceTag;

	return Hit.bBlockingHit ? Hit.ImpactPoint : Hit.TraceEnd;
}