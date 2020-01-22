
// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLItem.h"

AXLItem::AXLItem()
{
	//WeaponState = CreateDefaultSubobject<USSWeaponState>(TEXT("WeaponState"));
	ItemSounds = CreateDefaultSubobject<UXLItemSoundManager>(TEXT("ItemSounds"));
	ItemAnimations = CreateDefaultSubobject<UXLItemAnimationManager>(TEXT("ItemAnimations"));

	Mesh1P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh1P"));
	Mesh1P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh1P->SetOnlyOwnerSee(true);
	Mesh1P->SetOwnerNoSee(true);
	Mesh1P->SetReceivesDecals(false);
	Mesh1P->SetCastShadow(false);
	Mesh1P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh1P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	Mesh1P->SetCollisionResponseToAllChannels(ECR_Ignore);
	RootComponent = Mesh1P;

	Mesh3P = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh3P"));
	Mesh3P->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::OnlyTickPoseWhenRendered;
	Mesh3P->SetReceivesDecals(false);
	Mesh3P->SetCastShadow(true);
	Mesh3P->SetCollisionObjectType(ECC_WorldDynamic);
	Mesh3P->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Mesh3P->SetCollisionResponseToChannel(COLLISION_WEAPON, ECR_Block);
	Mesh3P->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	//Mesh3P->SetCollisionResponseToChannel(COLLISION_PROJECTILE, ECR_Block);

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
}

void AXLItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DetachMeshFromPawn();
}

void AXLItem::Destroyed()
{
	Super::Destroyed();
}

void AXLItem::TogglePerspective()
{
	class AXLPlayerController* MyPC = Cast<AXLPlayerController>(Character->Controller);

	if (MyPC && MyPC->IsFirstPerson)
	{
		Mesh1P->SetOwnerNoSee(false);
		Mesh3P->SetOwnerNoSee(true);
	}
	else
	{
		Mesh1P->SetOwnerNoSee(true);
		Mesh3P->SetOwnerNoSee(false);
	}
}

void AXLItem::PlayFX_Implementation(UParticleSystem* FX, FName AttachPoint)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		FXComponent = NULL;
		if (FX)
		{
			FXComponent = UGameplayStatics::SpawnEmitterAttached(FX, Mesh3P, AttachPoint);
		}
	}
}
void AXLItem::StopFX_Implementation()
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		if (FXComponent)
		{
			FXComponent->DeactivateSystem();
			FXComponent = NULL;
		}
	}
}

void AXLItem::PlaySound_Implementation(USoundCue* Sound)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		AudioComponent = NULL;
		if (Sound && Character)
		{
			AudioComponent = UGameplayStatics::SpawnSoundAttached(Sound, Character->GetRootComponent());
		}
	}
}
void AXLItem::StopSound_Implementation()
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		if (AudioComponent)
		{
			AudioComponent->FadeOut(0.1f, 0.0f);
			AudioComponent = NULL;
		}
	}
}

void AXLItem::PlayAnimation_Implementation(class UAnimMontage* Animation, float InPlayRate)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		//USkeletalMeshComponent* UseMesh = GetMesh();
		if (Animation && Mesh3P && Mesh3P->AnimScriptInstance)
		{
			Mesh3P->AnimScriptInstance->Montage_Play(Animation, InPlayRate);
		}
	}
}
void AXLItem::StopAnimation_Implementation(class UAnimMontage* Animation)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		//USkeletalMeshComponent* UseMesh = GetMesh();
		if (Animation && Mesh3P && Mesh3P->AnimScriptInstance && Mesh3P->AnimScriptInstance->Montage_IsPlaying(Animation))
		{
			Mesh3P->AnimScriptInstance->Montage_Stop(Animation->BlendOut.GetBlendTime());
		}
	}
}

void AXLItem::AttachMeshToPawn()
{
	if (Character)
	{
		DetachMeshFromPawn();

		if (Character->IsLocallyControlled())
		{
			USkeletalMeshComponent* PawnMesh3p = Character->GetMesh();
			USkeletalMeshComponent* PawnMesh1p = Character->PerspectiveMesh;

			Mesh1P->AttachToComponent(PawnMesh1p, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
			Mesh3P->AttachToComponent(PawnMesh3p, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);

			TogglePerspective();
		}
		else
		{
			USkeletalMeshComponent* PawnMesh3p = Character->GetMesh();

			Mesh3P->AttachToComponent(PawnMesh3p, FAttachmentTransformRules::KeepRelativeTransform, AttachPoint);
		}
	}
}
void AXLItem::DetachMeshFromPawn()
{
	Mesh3P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
	Mesh1P->DetachFromComponent(FDetachmentTransformRules::KeepRelativeTransform);
}

float AXLItem::StartEquip(FName AttachPoint)
{
	Character->GetMesh()->SetAnimInstanceClass(AnimClass);
	this->AttachPoint = AttachPoint;

	float OriginalDuration = ItemAnimations->EquipAnim ? ItemAnimations->EquipAnim->CalculateSequenceLength() : 0.0f;
	float Rate = OriginalDuration / EquipDuration;
	if (ItemAnimations->EquipAnim)
	{
		Character->PlayAnimMontage(ItemAnimations->EquipAnim, Rate);
	}

	GetWorldTimerManager().SetTimer(TimerHandle_Equip, this, &AXLItem::StopEquip, EquipDuration, false);

	if (Character && Character->IsLocallyControlled())
	{
		PlaySound(ItemSounds->EquipCue);
	}
	return EquipDuration;
}
void AXLItem::StopEquip()
{
	DetachMeshFromPawn();
	AttachMeshToPawn();
}

float AXLItem::StartUnequip()
{
	// Set animclass back to default

	float OriginalDuration = ItemAnimations->UnequipAnim->CalculateSequenceLength();
	float Rate = OriginalDuration / UnequipDuration;

	Character->PlayAnimMontage(ItemAnimations->UnequipAnim, Rate);

	GetWorldTimerManager().SetTimer(TimerHandle_Unequip, this, &AXLItem::StopUnequip, UnequipDuration, false);

	if (Character && Character->IsLocallyControlled())
	{
		PlaySound(ItemSounds->UnequipCue);
	}
	return UnequipDuration;
}
void AXLItem::StopUnequip()
{
	DetachMeshFromPawn();
}

void AXLItem::Drop()
{
	this->Destroy();
}

void AXLItem::Activate() 
{
	// not implemented
}
void AXLItem::Deactivate()
{
	// not implemented
}