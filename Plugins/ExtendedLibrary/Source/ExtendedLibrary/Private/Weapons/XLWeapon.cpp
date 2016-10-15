
// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeapon.h"

AXLWeapon::AXLWeapon()
{
	//WeaponState = CreateDefaultSubobject<USSWeaponState>(TEXT("WeaponState"));

	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh3P"));
	Mesh3P->MeshComponentUpdateFlag = EMeshComponentUpdateFlag::OnlyTickPoseWhenRendered;
	Mesh3P->bReceivesDecals = false;
	Mesh3P->CastShadow = true;
	Mesh3P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Mesh3P->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//Mesh3P->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	if (Character)
	{
		//AttackSpeed = Character->CharacterAttributes->GetAttackSpeed();
	}
}


void AXLWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//if (AttackSpeed >= 0)
	//{
	//	AttackSpeed -= DeltaTime;
	//}
}

void AXLWeapon::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DetachMeshFromPawn();
}

void AXLWeapon::Destroyed()
{
	Super::Destroyed();
}

bool AXLWeapon::StartAttack()
{
	if (XLWeaponCan::Attack(this))
	{
		PlayWeaponFX();
		WeaponState = EWeaponState::Firing;

		//AttackSpeed = Character->CharacterAttributes->GetAttackSpeed();
		return true;
	}
	else
	{
		return false;
	}
}
void AXLWeapon::StopAttack()
{
	StopWeaponFX();
	WeaponState = EWeaponState::Idle;
}

void AXLWeapon::StartReload()
{

}
void AXLWeapon::StopReload()
{

}

void AXLWeapon::StartMelee()
{
	if (XLWeaponCan::Melee(this))
	{
		Melee();
	}
}
void AXLWeapon::StopMelee()
{
	//if (GetWeaponState()->GetWeaponState() == EWeaponState::Meleeing)
	{
		WeaponState = EWeaponState::Idle;
		//StopWeaponAnimation(GetWeaponEffects()->GetMeleeAnim());
	}
}

void AXLWeapon::Melee()
{
	/*StopAttack();
	//GetWeaponState()->SetWeaponState(EWeaponState::Meleeing);
	float AnimDuration = 0.0f;// PlayWeaponAnimation(GetWeaponEffects()->GetMeleeAnim());
	if (AnimDuration <= 0.0f)
	{
	AnimDuration = 0.3f;
	}

	GetWorldTimerManager().SetTimer(Melee_Timer, this, &AXLWeapon::StopMelee, AnimDuration, false);
	if (Role == ROLE_Authority)
	{
	TArray<struct FOverlapResult> OutOverlaps;
	TArray<AActor*> HitActors;

	FQuat Rotation = Instigator->GetTransform().GetRotation();
	FVector Start = Instigator->GetTransform().GetLocation() + Rotation.Rotator().Vector() * 100.0f;

	FCollisionShape CollisionHitShape;
	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(Instigator);

	FCollisionObjectQueryParams CollisionObjectTypes;
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_Pawn);
	CollisionObjectTypes.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);

	CollisionHitShape = FCollisionShape::MakeBox(FVector(60.0f, 60.0f, 0.5f));
	//GetWorld()->OverlapMultiByObjectType(OutOverlaps, Start, Rotation, CollisionParams, CollisionHitShape, CollisionObjectTypes);

	for (int i = 0; i < OutOverlaps.Num(); ++i)
	{
	if (OutOverlaps[i].GetActor() && !HitActors.Contains(OutOverlaps[i].GetActor()))
	{
	if (!OutOverlaps[i].GetActor() || HitActors.Contains(OutOverlaps[i].GetActor()))
	{
	return;
	}
	HitActors.AddUnique(OutOverlaps[i].GetActor());
	FHitResult AttackHitResult;
	const FDamageEvent AttackDamageEvent;
	ASSCharacter* GameCharacter = Cast<ASSCharacter>(OutOverlaps[i].GetActor());

	if (GameCharacter)
	{
	UGameplayStatics::ApplyDamage(OutOverlaps[i].GetActor(), 200.0f, Instigator->GetController(), Character->Controller, UDamageType::StaticClass());
	}
	}
	OutOverlaps.Empty();
	}
	}

	if (Character && Character->IsLocallyControlled())
	{
	//PlayWeaponSound(GetWeaponEffects()->GetMeleeSound());
	}*/
}

float AXLWeapon::PlayAnimation(class UAnimMontage* Animation, float InPlayRate)
{
	float Duration = 0.0f;
	if (Character)
	{
		UAnimMontage* UseAnim = Animation;
		if (UseAnim)
		{
			Duration = Character->PlayAnimMontage(UseAnim, InPlayRate);
		}
	}
	return Duration;
}
void AXLWeapon::StopAnimation(class UAnimMontage* Animation)
{
	if (Character)
	{
		UAnimMontage* UseAnim = Animation;
		if (UseAnim)
		{
			Character->StopAnimMontage(UseAnim);
		}
	}
}

UAudioComponent* AXLWeapon::PlayWeaponSound(USoundCue* Sound)
{
	UAudioComponent* AC = NULL;
	if (Sound && Character)
	{
		AC = UGameplayStatics::SpawnSoundAttached(Sound, Character->GetRootComponent());
	}
	return AC;
}

void AXLWeapon::PlayWeaponFX()
{
	/*if (WeaponEffects->GetMuzzleFX())
	{
		USkeletalMeshComponent* UseWeaponMesh = GetWeaponMesh();
		if (!WeaponEffects->IsLoopedMuzzleFX() || WeaponEffects->GetMuzzlePSC() == NULL)
		{
			if (Character != NULL)
			{
				AController* PlayerCon = Character->GetController();
				if (PlayerCon != NULL)
				{
					Mesh3P->GetSocketLocation(WeaponEffects->GetWeaponFXPoint());
					WeaponEffects->SetMuzzlePSC(UGameplayStatics::SpawnEmitterAttached(WeaponEffects->GetMuzzleFX(), Mesh3P, WeaponEffects->GetWeaponFXPoint()));
					WeaponEffects->GetMuzzlePSC()->bOwnerNoSee = false;
					WeaponEffects->GetMuzzlePSC()->bOnlyOwnerSee = false;
				}
			}
			else
			{
				WeaponEffects->SetMuzzlePSC(UGameplayStatics::SpawnEmitterAttached(WeaponEffects->GetMuzzleFX(), UseWeaponMesh, WeaponEffects->GetWeaponFXPoint()));
			}
		}
	}

	if (!WeaponEffects->IsLoopedFireAnim() || !WeaponEffects->IsPlayingFireAnim())
	{
		PlayWeaponAnimation(WeaponEffects->GetFireAnim());
		WeaponEffects->SetPlayingFireAnim(true);
	}

	if (WeaponEffects->GetFireLoopSound())
	{
		if (WeaponEffects->GetFireAC() == NULL)
		{
			WeaponEffects->SetFireAC(PlayWeaponSound(WeaponEffects->GetFireLoopSound()));
		}
	}
	else
	{
		PlayWeaponSound(WeaponEffects->GetFireStartSound());
	}*/
}
void AXLWeapon::StopWeaponFX()
{
	/*if (WeaponEffects->IsLoopedMuzzleFX())
	{
		if (WeaponEffects->GetMuzzlePSC() != NULL)
		{
			WeaponEffects->GetMuzzlePSC()->DeactivateSystem();
			WeaponEffects->SetMuzzlePSC(NULL);
		}
	}

	if (WeaponEffects->IsLoopedFireAnim() && WeaponEffects->IsPlayingFireAnim())
	{
		StopWeaponAnimation(WeaponEffects->GetFireAnim());
		WeaponEffects->SetPlayingFireAnim(false);
	}

	if (WeaponEffects->GetFireAC())
	{
		WeaponEffects->GetFireAC()->FadeOut(0.1f, 0.0f);
		WeaponEffects->SetFireAC(NULL);

		PlayWeaponSound(WeaponEffects->GetFireFinishSound());
	}*/
}

void AXLWeapon::AttachMeshToPawn()
{
	if (Character)
	{
		DetachMeshFromPawn();

		FName AttachPoint = "RightHand";
		USkeletalMeshComponent* PawnMesh3p = Character->GetMesh();
		Mesh3P->SetHiddenInGame(false);
		Mesh3P->AttachToComponent(PawnMesh3p, FAttachmentTransformRules::KeepWorldTransform, AttachPoint);
	}
}
void AXLWeapon::DetachMeshFromPawn()
{
	Mesh3P->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
	Mesh3P->SetHiddenInGame(true);
}
