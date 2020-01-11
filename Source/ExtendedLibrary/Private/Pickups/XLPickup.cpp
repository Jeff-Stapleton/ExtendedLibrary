#include "ExtendedLibraryPCH.h"
#include "Pickups/XLPickup.h"
#include "Particles/ParticleSystemComponent.h"

AXLPickup::AXLPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PickupSounds = CreateDefaultSubobject<UXLPickupSoundManager>(TEXT("PickupSounds"));
	Component = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Component"));
	MovementComp = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("Movement"));

	//MovementComp->InitialSpeed = 600.0f;
	//MovementComp->MaxSpeed = 600.0f;
	//MovementComp->bRotationFollowsVelocity = false;
	//MovementComp->ProjectileGravityScale = 1.0f;

	bIsActive = false;
	PickedUpBy = NULL;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;

	RootComponent = Component;
}

void AXLPickup::BeginPlay()
{
	Super::BeginPlay();

	Component->SetSimulatePhysics(IsPhysicsEnabled);

	bIsActive = true;
	PickedUpBy = NULL;
}

void AXLPickup::DestroyPickup()
{
	if (Role == ROLE_Authority)
	{
		Super::Destroy();
	}
	else
	{
		ServerDestroyPickup();
	}
}
bool AXLPickup::ServerDestroyPickup_Validate()
{
	return true;
}
void AXLPickup::ServerDestroyPickup_Implementation()
{
	DestroyPickup();
}

void AXLPickup::OnPickedUp(class AXLCharacter* Pawn)
{
	if (XLPickupCan::BePickedUp(this, Pawn))
	{
		bIsActive = false;
		PickedUpBy = Pawn;
		PlaySound();
		OnPickedUpEvent();
	}
}

void AXLPickup::PlaySound()
{
	if (PickupSounds->PickupSound && PickedUpBy)
	{
		UGameplayStatics::SpawnSoundAttached(PickupSounds->PickupSound, PickedUpBy->GetRootComponent());
	}
}

void AXLPickup::OnRep_IsActive()
{
	// OnPickedUp();
}

void AXLPickup::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( AXLPickup, bIsActive );
	DOREPLIFETIME( AXLPickup, PickedUpBy );
}