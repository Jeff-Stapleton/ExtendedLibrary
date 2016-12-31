#include "ExtendedLibraryPCH.h"
#include "Pickups/XLPickup.h"
#include "Particles/ParticleSystemComponent.h"

AXLPickup::AXLPickup(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PickupEffects = CreateDefaultSubobject<UXLPickupEffectManager>(TEXT("PickupEffects"));
	PickupSounds = CreateDefaultSubobject<UXLPickupSoundManager>(TEXT("PickupSounds"));

	UCapsuleComponent* CollisionComp = ObjectInitializer.CreateDefaultSubobject<UCapsuleComponent>(this, TEXT("CollisionComp"));
	CollisionComp->InitCapsuleSize(40.0f, 50.0f);
	//CollisionComp->SetCollisionObjectType(COLLISION_PICKUP);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	PickupPSC = ObjectInitializer.CreateDefaultSubobject<UParticleSystemComponent>(this, TEXT("PickupFX"));
	PickupPSC->bAutoActivate = false;
	PickupPSC->bAutoDestroy = false;
	PickupPSC->SetupAttachment(RootComponent);

	RespawnTime = 10.0f;
	bIsActive = false;
	PickedUpBy = NULL;

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
}

void AXLPickup::BeginPlay()
{
	Super::BeginPlay();

	RespawnPickup();
}

void AXLPickup::NotifyActorBeginOverlap(class AActor* Other)
{
	Super::NotifyActorBeginOverlap(Other);
	PickupOnTouch(Cast<AXLCharacter>(Other));
}

void AXLPickup::GivePickupTo(class AXLCharacter* Pawn)
{
}

void AXLPickup::PickupOnTouch(class AXLCharacter* Pawn)
{
	if (XLPickupCan::BePickedUp(this, Pawn))
	{
		bIsActive = false;
		GivePickupTo(Pawn);
		PickedUpBy = Pawn;
		OnPickedUp();

		if (RespawnTime > 0.0f)
		{
			GetWorldTimerManager().SetTimer(TimerHandle_RespawnPickup, this, &AXLPickup::RespawnPickup, RespawnTime, false);
		}
	}
}

void AXLPickup::RespawnPickup()
{
	bIsActive = true;
	PickedUpBy = NULL;
	OnRespawned();

	TSet<AActor*> OverlappingPawns;
	GetOverlappingActors(OverlappingPawns, AXLCharacter::StaticClass());

	for (AActor* OverlappingPawn : OverlappingPawns)
	{
		PickupOnTouch(CastChecked<AXLCharacter>(OverlappingPawn));	
	}
}

void AXLPickup::OnPickedUp()
{
	if (PickupEffects->RespawningFX)
	{
		PickupPSC->SetTemplate(PickupEffects->RespawningFX);
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

void AXLPickup::OnRespawned()
{
	if (PickupEffects->ActiveFX)
	{
		PickupPSC->SetTemplate(PickupEffects->ActiveFX);
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

void AXLPickup::OnRep_IsActive()
{
	if (bIsActive)
	{
		OnRespawned();
	}
	else
	{
		OnPickedUp();
	}
}

void AXLPickup::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps( OutLifetimeProps );

	//DOREPLIFETIME( AXLPickup, bIsActive );
	//DOREPLIFETIME( AXLPickup, PickedUpBy );
}