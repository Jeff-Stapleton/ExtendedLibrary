
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

UAudioComponent* AXLItem::PlaySound(USoundCue* Sound)
{
	UAudioComponent* AC = NULL;
	if (Sound && Character)
	{
		AC = UGameplayStatics::SpawnSoundAttached(Sound, Character->GetRootComponent());
	}
	return AC;
}

float AXLItem::PlayAnimation(class UAnimMontage* Animation, float InPlayRate)
{
	float Duration = 0.5f;
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
void AXLItem::StopAnimation(class UAnimMontage* Animation)
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

void AXLItem::PlayFX()
{

}
void AXLItem::StopFX()
{

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

float AXLItem::StartEquip(FName attachPoint)
{
	AttachPoint = attachPoint;

	float Duration = PlayAnimation(ItemAnimations->EquipAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Equip, this, &AXLItem::StopEquip, Duration, false);

	if (Character && Character->IsLocallyControlled())
	{
		PlaySound(ItemSounds->EquipCue);
	}
	return Duration;
}
void AXLItem::StopEquip()
{
	DetachMeshFromPawn();
	AttachMeshToPawn();
	Character->GetMesh()->SetAnimInstanceClass(AnimClass);
}

float AXLItem::StartUnequip()
{
	float Duration = PlayAnimation(ItemAnimations->UnequipAnim);

	GetWorldTimerManager().SetTimer(TimerHandle_Unequip, this, &AXLItem::StopUnequip, Duration, false);

	if (Character && Character->IsLocallyControlled())
	{
		PlaySound(ItemSounds->UnequipCue);
	}
	return Duration;
}
void AXLItem::StopUnequip()
{
	DetachMeshFromPawn();
}

void AXLItem::Drop()
{
	this->Destroy();
}