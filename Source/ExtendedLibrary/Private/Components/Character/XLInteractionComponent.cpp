// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLInteractionComponent.h"

void UXLInteractionComponent::Inspect()
{
	FHitResult Trace(ForceInit);
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("InspectTrace")), true, GetOwner());
	bool Hit = InteractTrace(&Trace, &TraceParams);

	IXLInteractionInterface* InspectionTarget = Cast<IXLInteractionInterface>(Trace.GetActor());
	if (InspectionTarget)
	{
		InspectionTarget->Execute_OnInspect(Cast<UObject>(InspectionTarget), GetOwner());
	}
}

void UXLInteractionComponent::Interact()
{
	FHitResult Trace(ForceInit);
	FCollisionQueryParams TraceParams = FCollisionQueryParams(FName(TEXT("InteractionTrace")), true, GetOwner());
	//GetWorld()->DebugDrawTraceTag = "InteractionTrace";
	bool Hit = InteractTrace(&Trace, &TraceParams);

	IXLInteractionInterface* InteractionTarget = Cast<IXLInteractionInterface>(Trace.GetActor());
	if (InteractionTarget)
	{
		InteractionTarget->Execute_OnInteract(Cast<UObject>(InteractionTarget), GetOwner());
	}
}

bool UXLInteractionComponent::InteractTrace(FHitResult* RV_Hit, FCollisionQueryParams* RV_TraceParams)
{
	AXLActionCharacter* Owner = Cast<AXLActionCharacter>(GetOwner());
	if (Owner && Owner->Camera)
	{
		FVector Start = Owner->Camera->GetComponentLocation();
		FVector End = Owner->Camera->GetComponentLocation() + (Owner->Camera->GetForwardVector() * InteractDistance);

		RV_TraceParams->bTraceComplex = true;
		RV_TraceParams->bTraceAsyncScene = true;
		RV_TraceParams->bReturnPhysicalMaterial = true;
		RV_TraceParams->AddIgnoredActor(GetOwner());

		bool DidTrace = GetWorld()->LineTraceSingleByChannel(*RV_Hit, Start, End, ECC_Camera, *RV_TraceParams);

		return DidTrace;
	}
	return false;
}