// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLMeleeWeapon.h"

AXLMeleeWeapon::AXLMeleeWeapon()
{

}

void AXLMeleeWeapon::StartAttack()
{
	Super::StartAttack();

	//if (XLWeaponCan::Attack(this))
	if (WeaponState == EWeaponState::Firing)
	{
		/*if (WeaponResources->CurrentClipAmmo > 0 || WeaponResources->InfiniteAmmo)
		{
			const float GameTime = GetWorld()->GetTimeSeconds();
			if (LastAttackTime > 0 && WeaponStats->TimeBetweenAttacks > 0.0f && LastAttackTime + WeaponStats->TimeBetweenAttacks > GameTime)
			{
				GetWorldTimerManager().SetTimer(FiringTimer, this, &AXLMeleeWeapon::SwingWeapon, LastAttackTime + WeaponStats->TimeBetweenAttacks - GameTime, false);
			}
			else
			{
				SwingWeapon();
			}
		}
		else if (WeaponResources->CurrentAmmo >= 0)
		{
			StopAttack();
		}
		else if (Character && Character->IsLocallyControlled())
		{
			PlaySound(WeaponSounds->OutOfAmmoSound);
		}*/
	}
	else
	{
		StopAttack();
	}
}
void AXLMeleeWeapon::StopAttack()
{
	Super::StopAttack();
	{
		//GetWorldTimerManager().ClearTimer(FiringTimer);
		WeaponState = EWeaponState::Idle;
	}
}

void AXLMeleeWeapon::SwingWeapon()
{
	FVector CharacterLocation = GetMeleeLocation();
	FRotator CharacterRotation = GetMeleeRotation();

	FVector AimLoc;
	FRotator AimRot;

	Character->Controller->GetActorEyesViewPoint(AimLoc, AimRot);

	//float test = WeaponStats->ShotNumber / (WeaponStats->ShotNumber / 4);
	//float Offset = WeaponStats->ShotNumber / 2;

	//for (int i = 0; i < WeaponStats->ShotNumber; i++)
	//{
	//	float test2 = test * i;
	//	float poop = (CharacterRotation.Yaw + test2) + Offset;

	//	FVector test3 = FRotator(AimRot.Pitch, poop, 0.0).Vector();
	//	FVector test4 = test3 * WeaponStats->MaxRange;
	//	FVector test5 = test4 + CharacterLocation;

	//	const FHitResult Impact = WeaponTrace(CharacterLocation, test5);

	//	ApplyAttackDamage(Impact, test4);
	//	ApplyAttackForce(Impact);

	//	//SpawnImpactEffects(Impact);
	//	//SpawnTrailEffect(Impact.GetActor() ? Impact.ImpactPoint : End);
	//}

	////UseAmmo();

	//if (FireMode == EFireMode::Automatic)
	//{
	//	GetWorldTimerManager().SetTimer(FiringTimer, this, &AXLMeleeWeapon::StartAttack, WeaponStats->TimeBetweenAttacks, false);
	//}
}

void AXLMeleeWeapon::ApplyAttackDamage(const FHitResult& Impact, const FVector& ShootDir)
{
    if (Impact.GetActor())
    {
        //FPointDamageEvent PointDmg;
        //PointDmg.DamageTypeClass = WeaponStats->DamageType;// DamageType;
        //PointDmg.HitInfo = Impact;
        //PointDmg.ShotDirection = ShootDir;
        //PointDmg.Damage = FMath::RandRange(WeaponStats->MinDamage, WeaponStats->MaxDamage);

        //Impact.GetActor()->TakeDamage(PointDmg.Damage, PointDmg, Character->Controller, this);
    }
}

void AXLMeleeWeapon::ApplyAttackForce(const FHitResult& Impact)
{
	if ((Impact.GetComponent() != nullptr) && Impact.GetComponent()->IsSimulatingPhysics())
	{
		//Impact.GetComponent()->AddForce((WeaponStats->Force * Impact.ImpactNormal), Impact.BoneName);
	}
}

FVector AXLMeleeWeapon::GetMeleeLocation()
{
	class AXLPlayerController* MyPC = Cast<AXLPlayerController>(Character->Controller);

	if (MyPC->IsFirstPerson)
	{
		return Mesh1P->GetSocketLocation(FName(TEXT("Camera")));
	}
	else
	{
		return Mesh3P->GetSocketLocation(FName(TEXT("_meleeSource")));
	}
}

FRotator AXLMeleeWeapon::GetMeleeRotation()
{
	class AXLPlayerController* MyPC = Cast<AXLPlayerController>(Character->Controller);

	if (MyPC->IsFirstPerson)
	{
		return Mesh1P->GetSocketRotation(FName(TEXT("Camera")));
	}
	else
	{
		return Mesh3P->GetSocketRotation(FName(TEXT("_meleeSource")));
	}
}

void AXLMeleeWeapon::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AXLMeleeWeapon, WeaponState);
}