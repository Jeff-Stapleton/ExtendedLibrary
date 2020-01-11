#include "ExtendedLibraryPCH.h"
#include "Pickups/XLOverlapPickup.h"
#include "Particles/ParticleSystemComponent.h"

AXLOverlapPickup::AXLOverlapPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OverlapVolume = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("OverlapVolume"));

	OverlapVolume->SetupAttachment(RootComponent);
	OverlapVolume->InitCapsuleSize(40.0f, 50.0f);
	OverlapVolume->SetCollisionObjectType(COLLISION_PICKUP);
	OverlapVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	OverlapVolume->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);

	//MovementComp->UpdatedComponent = OverlapVolume;
}

void AXLOverlapPickup::NotifyActorBeginOverlap(class AActor* Other)
{
	AXLCharacter* Pawn = Cast<AXLCharacter>(Other);
	if (XLPickupCan::BePickedUp(this, Pawn))
	{
		Super::NotifyActorBeginOverlap(Pawn);

		OnPickedUp(Cast<AXLCharacter>(Pawn));
	}
}

void AXLOverlapPickup::OnPickedUp(class AXLCharacter* Pawn)
{
	Super::OnPickedUp(Pawn);
}