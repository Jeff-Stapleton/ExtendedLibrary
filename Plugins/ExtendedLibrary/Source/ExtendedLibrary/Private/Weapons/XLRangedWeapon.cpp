// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLRangedWeapon.h"

AXLRangedWeapon::AXLRangedWeapon()
{

}


void AXLRangedWeapon::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AXLRangedWeapon::Destroyed()
{
	Super::Destroyed();

	StopAttackFX();
}

/////////////////////////////////////////// Input handlers //////////////////////////////////////////

bool AXLRangedWeapon::StartAttack()
{
	if (Super::StartAttack())
	{
		const int32 RandomSeed = FMath::Rand();
		FRandomStream WeaponRandomStream(RandomSeed);
		const float CurrentSpread = GetCurrentSpread();
		const float ConeHalfAngle = FMath::DegreesToRadians(CurrentSpread * 0.5f);

		const FVector AimDir = Character->GetActorForwardVector();
		const FVector StartTrace = GetMuzzleLocation();
		const FVector ShootDir = WeaponRandomStream.VRandCone(AimDir, ConeHalfAngle, ConeHalfAngle);
		const FVector EndTrace = StartTrace + ShootDir * 1000.0f;

		const FHitResult Impact = WeaponTrace(StartTrace, EndTrace);
		ProcessInstantHit(Impact, StartTrace, ShootDir, RandomSeed, CurrentSpread);

		return true;
	}
	else
	{
		return false;
	}
}
void AXLRangedWeapon::StopAttack()
{
	Super::StopAttack();
	//if (WeaponState->GetWeaponState() == EWeaponState::Firing)
	{
		WeaponState = EWeaponState::Idle;
		//OnBurstFinished();
	}
}

void AXLRangedWeapon::StartReload()
{
	if (XLWeaponCan::Reload(this))
	{

	}
}
void AXLRangedWeapon::StopReload()
{
	//if (WeaponState->GetWeaponState() == EWeaponState::Reloading)
	{
		WeaponState = EWeaponState::Idle;
		//StopWeaponAnimation(WeaponEffects->GetReloadAnim());
	}
}

void AXLRangedWeapon::ProcessInstantHit(const FHitResult& Impact, const FVector& Origin, const FVector& ShootDir, int32 RandomSeed, float ReticleSpread)
{
	//if (Impact.GetActor())
	//{
	//	FPointDamageEvent PointDmg;
	//	PointDmg.DamageTypeClass = DamageType;
	//	PointDmg.HitInfo = Impact;
	//	PointDmg.ShotDirection = ShootDir;
	//	PointDmg.Damage = Character->CharacterAttributes->GetAttackPower();

	//	Impact.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, Character->Controller, this);
	//}
	/////////////////////////////////////////////////////////////////////////////////////

	//const FVector EndTrace = Origin + ShootDir * 1000.0f;
	//const FVector EndPoint = Impact.GetActor() ? Impact.ImpactPoint : EndTrace;
	//SpawnTrailEffect(EndPoint);
	//SpawnImpactEffects(Impact);
}

void AXLRangedWeapon::SpawnTrailEffect(const FVector& EndPoint)
{
	//if (WeaponEffects->GetTrailFX())
	//{
	//	const FVector Origin = GetMuzzleLocation();

	//	UParticleSystemComponent* TrailPSC = UGameplayStatics::SpawnEmitterAtLocation(this, WeaponEffects->GetTrailFX(), Origin);
	//	if (TrailPSC)
	//	{
	//		TrailPSC->SetVectorParameter(WeaponEffects->GetTrailFXParams(), EndPoint);
	//	}
	//}
}

void AXLRangedWeapon::SpawnImpactEffects(const FHitResult& Impact)
{
	//if (ImpactTemplate && Impact.bBlockingHit)
	//{
	//	FHitResult UseImpact = Impact;

	//	// trace again to find component lost during replication
	//	if (!Impact.Component.IsValid())
	//	{
	//		const FVector StartTrace = Impact.ImpactPoint + Impact.ImpactNormal * 10.0f;
	//		const FVector EndTrace = Impact.ImpactPoint - Impact.ImpactNormal * 10.0f;
	//		FHitResult Hit = WeaponTrace(StartTrace, EndTrace);
	//		UseImpact = Hit;
	//	}

	//	FTransform const SpawnTransform(Impact.ImpactNormal.Rotation(), Impact.ImpactPoint);
	//	ASSImpactEffect* EffectActor = GetWorld()->SpawnActorDeferred<ASSImpactEffect>(ImpactTemplate, SpawnTransform);
	//	if (EffectActor)
	//	{
	//		EffectActor->SurfaceHit = UseImpact;
	//		UGameplayStatics::FinishSpawningActor(EffectActor, SpawnTransform);
	//	}
	//}
}

FVector AXLRangedWeapon::GetMuzzleLocation()
{
	USkeletalMeshComponent* UseMesh = Mesh3P;
	return UseMesh->GetSocketLocation(FName(TEXT("Muzzle")));
}

float AXLRangedWeapon::GetCurrentSpread() const
{
	/*float FinalSpread = WeaponAttributes->GetAccuracy();
	if (Character)
	{
	if (Character->GetPlayerState()->GetPlayerState() == EPlayerState::Crouching || Character->GetPlayerState()->GetPlayerState() == EPlayerState::Covering)
	{
	if (WeaponState->GetTargetingState() == ETargetingState::Targeting || ETargetingState::Scoping)
	{
	FinalSpread = WeaponAttributes->GetAccuracy() * 0.25;
	}
	else
	{
	FinalSpread = WeaponAttributes->GetAccuracy() * 0.75;
	}
	}
	else
	{
	if (WeaponState->GetTargetingState() == ETargetingState::Targeting)
	{
	FinalSpread = WeaponAttributes->GetAccuracy() * 0.5;
	}
	else
	{
	FinalSpread = WeaponAttributes->GetAccuracy();
	}
	}
	}

	return FinalSpread;*/
	return 0.0f;
}

FHitResult AXLRangedWeapon::WeaponTrace(const FVector& StartTrace, const FVector& EndTrace)
{
	//static FName WeaponFireTag = FName(TEXT("WeaponTrace"));

	//FCollisionQueryParams TraceParams(WeaponFireTag, true, Instigator);
	//TraceParams.bTraceAsyncScene = true;
	//TraceParams.bReturnPhysicalMaterial = true;

	FHitResult Hit(ForceInit);
	//GetWorld()->LineTraceSingle(Hit, StartTrace, EndTrace, Channel, TraceParams);

	return Hit;
}

////////////////////////////////////////// Particle Effects /////////////////////////////////////////

void AXLRangedWeapon::PlayAttackFX()
{
	//if (WeaponEffects->GetMuzzleFX())
	//{
	//	USkeletalMeshComponent* UseWeaponMesh = GetWeaponMesh();
	//	if (WeaponEffects->GetMuzzlePSC() == NULL)
	//	{
	//		//Split screen requires we create 2 effects. One that we see and one that the other player sees.
	//		if (Character && Character->IsLocallyControlled())
	//		{
	//			AController* PlayerCon = Character->GetController();
	//			if (PlayerCon != NULL)
	//			{
	//				Mesh3P->GetSocketLocation(MuzzleAttachPoint);
	//				WeaponEffects->SetMuzzlePSC(UGameplayStatics::SpawnEmitterAttached(WeaponEffects->GetMuzzleFX(), Mesh3P, MuzzleAttachPoint));
	//				WeaponEffects->GetMuzzlePSC()->bOwnerNoSee = false;
	//				WeaponEffects->GetMuzzlePSC()->bOnlyOwnerSee = true;
	//			}
	//		}
	//		else
	//		{
	//			WeaponEffects->SetMuzzlePSC(UGameplayStatics::SpawnEmitterAttached(WeaponEffects->GetMuzzleFX(), UseWeaponMesh, MuzzleAttachPoint));
	//		}
	//	}
	//}

	//if (!WeaponEffects->IsPlayingFireAnim())
	//{
	//	PlayWeaponAnimation(WeaponEffects->GetFireAnim());
	//	WeaponEffects->SetPlayingFireAnim(true);
	//}

	////if (WeaponAttributes->GetFireMode() == EFireMode::Automatic)
	//{
	//	if (WeaponEffects->GetFireAC() == NULL)
	//	{
	//		WeaponEffects->SetFireAC(PlayWeaponSound(WeaponEffects->GetFireLoopSound()));
	//	}
	//}
	////else
	//{
	//	PlayWeaponSound(WeaponEffects->GetFireStartSound());
	//}

	///*ASSPlayerController* PC = (Character != NULL) ? Cast<ASSPlayerController>(Character->Controller) : NULL;
	//if (PC != NULL && PC->IsLocalController())
	//{
	//if (WeaponEffects->GetCameraShake() && WeaponAttributes->GetFireMode() == EFireMode::Automatic)
	//{
	//PC->ClientPlayCameraShake(WeaponEffects->GetCameraShake(), 1 - (WeaponAttributes->GetStability() * 0.01f));
	//}
	//if (FireForceFeedback != NULL)
	//{
	//PC->ClientPlayForceFeedback(FireForceFeedback, false, "Weapon");
	//}
	//}*/
}

void AXLRangedWeapon::StopAttackFX()
{
	/*if (WeaponAttributes->GetFireMode() == EFireMode::Automatic)
	{
	if (WeaponEffects->GetMuzzlePSC() != NULL)
	{
	WeaponEffects->GetMuzzlePSC()->DeactivateSystem();
	WeaponEffects->SetMuzzlePSC(NULL);
	}
	}
	if (WeaponAttributes->GetFireMode() == EFireMode::Automatic && WeaponEffects->IsPlayingFireAnim())
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

