#include "ExtendedLibraryPCH.h"
#include "Pickups/XLOverlapPickup.h"
#include "Particles/ParticleSystemComponent.h"
#include "Cans/XLPickupCan.h"

AXLOverlapPickup::AXLOverlapPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	OverlapVolume = ObjectInitializer.CreateDefaultSubobject<USphereComponent>(this, TEXT("OverlapVolume"));
	OverlapVolume->InitSphereRadius(50.0f);
	OverlapVolume->AlwaysLoadOnClient = true;
	OverlapVolume->AlwaysLoadOnServer = true;
	OverlapVolume->bTraceComplexOnMove = true;
	OverlapVolume->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	OverlapVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapVolume->SetCollisionObjectType(COLLISION_PICKUP);
	OverlapVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapVolume->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	OverlapVolume->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Block);
	OverlapVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	RootComponent = OverlapVolume;

	Component->SetupAttachment(RootComponent);

	MovementComp->UpdatedComponent = OverlapVolume;
}

void AXLOverlapPickup::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetInstigator())
	{
		OverlapVolume->MoveIgnoreActors.Add(GetInstigator());
	}
}

void AXLOverlapPickup::NotifyActorBeginOverlap(class AActor* Other)
{
	AXLCharacter* Pawn = Cast<AXLCharacter>(Other);
	if (XLPickupCan::BePickedUp(this, Pawn))
	{
		Super::NotifyActorBeginOverlap(Pawn);

		PickedUp(Cast<AXLCharacter>(Pawn));
	}
}
