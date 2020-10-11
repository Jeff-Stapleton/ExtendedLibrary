#include "ExtendedLibraryPCH.h"
#include "Pickups/XLPickup.h"
#include "Cans/XLPickupCan.h"
#include "Particles/ParticleSystemComponent.h"

AXLPickup::AXLPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PickupSounds = CreateDefaultSubobject<UXLPickupSoundManager>(TEXT("PickupSounds"));

	Component = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("Component"));

	MovementComp = ObjectInitializer.CreateDefaultSubobject<UProjectileMovementComponent>(this, TEXT("Movement"));
	MovementComp->InitialSpeed = 500.0f;
	MovementComp->MaxSpeed = 750.0f;
	MovementComp->bRotationFollowsVelocity = false;
	MovementComp->ProjectileGravityScale = 1.0f;

	PickupPSC = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("PickupFX"));
	PickupPSC->bAutoActivate = false;
	PickupPSC->bAutoDestroy = false;
	PickupPSC->SetupAttachment(RootComponent);

	RootComponent = Component;

	RespawnTime = 10.0f;
	bIsActive = false;
	PickedUpBy = NULL;

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	SetReplicatingMovement(true);
}

void AXLPickup::BeginPlay()
{
	Super::BeginPlay();

	Respawn();
}

void AXLPickup::InitVelocity(FVector& ShootDirection)
{
	if (MovementComp)
	{
		MovementComp->Velocity = ShootDirection * MovementComp->InitialSpeed;
	}
}


void AXLPickup::PickedUp(class AXLCharacter* Pawn)
{
	if (XLPickupCan::BePickedUp(this, Pawn))
	{
		PickedUpBy = Pawn;
		if (!IsPendingKill())
		{
			bIsActive = false;
			OnPickedUp();

			if (RespawnTime > 0.0f)
			{
				GetWorldTimerManager().SetTimer(TimerHandle_RespawnPickup, this, &AXLPickup::Respawn, RespawnTime, false);
			}
		}
	}
}

void AXLPickup::OnPickedUp()
{
	if (RespawningFX)
	{
		PickupPSC->SetTemplate(RespawningFX);
		PickupPSC->ActivateSystem();
	}
	else
	{
		PickupPSC->DeactivateSystem();
	}

	if (PickupSounds->PickupSound && PickedUpBy)
	{
		UGameplayStatics::SpawnSoundAttached(PickupSounds->PickupSound, PickedUpBy->GetRootComponent());
	}

	OnPickedUpEvent();
}

void AXLPickup::Respawn()
{
	bIsActive = true;
	PickedUpBy = NULL;
	OnRespawn();

	TSet<AActor*> OverlappingPawns;
	GetOverlappingActors(OverlappingPawns, AXLPickup::StaticClass());

	for (AActor* OverlappingPawn : OverlappingPawns)
	{
		PickedUp(CastChecked<AXLCharacter>(OverlappingPawn));
	}
}

void AXLPickup::OnRespawn()
{
	if (ActiveFX)
	{
		PickupPSC->SetTemplate(ActiveFX);
		PickupPSC->ActivateSystem();
	}
	else
	{
		PickupPSC->DeactivateSystem();
	}

	const bool bJustSpawned = CreationTime <= (GetWorld()->GetTimeSeconds() + 5.0f);
	if (PickupSounds->RespawnSound && !bJustSpawned)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickupSounds->RespawnSound, GetActorLocation());
	}

	OnRespawnEvent();
}

void AXLPickup::DestroyPickup()
{
	if (GetLocalRole() == ROLE_Authority)
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

void AXLPickup::OnRep_IsActive()
{
	if (bIsActive)
	{
		OnRespawn();
	}
	else
	{
		OnPickedUp();
	}
}

void AXLPickup::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	DOREPLIFETIME( AXLPickup, bIsActive );
	DOREPLIFETIME( AXLPickup, PickedUpBy );
}
