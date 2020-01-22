
// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLWeapon.h"

AXLWeapon::AXLWeapon()
{
	//WeaponAnimations = CreateDefaultSubobject<UXLWeaponAnimationManager>(TEXT("WeaponAnimations"));
	//WeaponEffects = CreateDefaultSubobject<UXLWeaponEffectManager>(TEXT("WeaponEffects"));
	//WeaponSounds = CreateDefaultSubobject<UXLWeaponSoundManager>(TEXT("WeaponSounds"));

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;
	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bNetUseOwnerRelevancy = true;
}


void AXLWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AXLWeapon::SetOwner(AActor* NewOwner)
{
	Super::SetOwner(NewOwner);
	
	if (NewOwner)
	{
		Character = Cast<AXLCharacter>(NewOwner);
		Instigator = Cast<AXLCharacter>(NewOwner);

		class AXLPlayerController* MyPC = Cast<AXLPlayerController>(Character->Controller);
		if (MyPC)
		{
			MyPC->OnTestDelegate.AddDynamic(this, &AXLWeapon::TogglePerspective);
		}
	}
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

void AXLWeapon::TogglePerspective()
{
	Super::TogglePerspective();

	class AXLPlayerController* MyPC = Cast<AXLPlayerController>(Character->Controller);

	if (MyPC && MyPC->IsFirstPerson)
	{
		/*if (WeaponEffects->MuzzlePSC1P)
		{
			WeaponEffects->MuzzlePSC3P->bOwnerNoSee = true;

			WeaponEffects->MuzzlePSC1P->bOwnerNoSee = false;
			WeaponEffects->MuzzlePSC1P->bOnlyOwnerSee = true;
		}*/
	}
	else
	{
		/*if (WeaponEffects->MuzzlePSC1P)
		{
			WeaponEffects->MuzzlePSC3P->bOwnerNoSee = false;

			WeaponEffects->MuzzlePSC1P->bOwnerNoSee = true;
			WeaponEffects->MuzzlePSC1P->bOnlyOwnerSee = false;
		}*/
	}
}

/////////////////////////////////////////////INPUT/////////////////////////////////////////////

float AXLWeapon::StartUnequip()
{
	float Duration = Super::StartUnequip();

	if (/*WeaponState == EWeaponState::Reloading*/true)
	{
		//StopAnimation(WeaponAnimations->ReloadAnim);
		//GetWorldTimerManager().ClearTimer(TimerHandle_Reload);
	}
	return Duration;
}

void AXLWeapon::StartAttack()
{
	//if (true)
	//{
	//	WeaponState = EWeaponState::Firing;
	//}
}
void AXLWeapon::StopAttack()
{
	/*WeaponState = EWeaponState::Idle;*/
}

void AXLWeapon::StartReload()
{
	return;
}
void AXLWeapon::StopReload()
{

}

void AXLWeapon::StartMelee()
{
	if (true)
	{
		Melee();
	}
}
void AXLWeapon::StopMelee()
{
	//WeaponState = EWeaponState::Idle;
	//StopAnimation(WeaponAnimations->MeleeAnim);
}

void AXLWeapon::Melee()
{

}

////////////////////////////////////////////VISUALS////////////////////////////////////////////

void AXLWeapon::PlayWeaponSound()
{
	/*if (WeaponSounds->FireLoopSound)
	{
		if (WeaponSounds->FireAC == NULL)
		{
			WeaponSounds->FireAC = PlaySound(WeaponSounds->FireLoopSound);
		}
	}
	else
	{
		PlaySound(WeaponSounds->FireSound);
	}*/
}
void AXLWeapon::StopWeaponSound()
{
	//if (WeaponSounds->FireAC)
	//{
	//	WeaponSounds->FireAC->FadeOut(0.1f, 0.0f);
	//	WeaponSounds->FireAC = NULL;

	//	PlaySound(WeaponSounds->FireFinishSound);
	//}
}

//////////////////////////////////////////UTILITIES///////////////////////////////////////////

FHitResult AXLWeapon::WeaponTrace(const FVector& Start, const FVector& End)
{
	static FName WeaponFireTag = FName(TEXT("WeaponTrace"));

	FCollisionQueryParams TraceParams(WeaponFireTag, true, Character);
	TraceParams.bTraceAsyncScene = true;
	TraceParams.bReturnPhysicalMaterial = true;

	//GetWorld()->DebugDrawTraceTag = WeaponFireTag;

	FHitResult Hit(ForceInit);
	GetWorld()->LineTraceSingleByChannel(Hit, Start, End, COLLISION_PROJECTILE, TraceParams);

	return Hit;
}
