// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLCharacter.h"

AXLCharacter::AXLCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AXLCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AXLCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


float AXLCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	/*ASSPlayerController* MyPC = Cast<ASSPlayerController>(Controller);
	if (CharacterAttributes->GetCurrentHealth() <= 0.f)
	{
		return 0.f;
	}

	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage != 0.f)
	{
		if (CharacterAttributes->GetCurrentShield() > 0 && ActualDamage > 0)
		{
			float temp = ActualDamage - CharacterAttributes->GetCurrentShield();
			//CharacterAttributes->SetCurrentShield(CharacterAttributes->GetCurrentShield() - ActualDamage);
			if (temp > 0)
			{
				ActualDamage = temp;
			}
		}
		if (CharacterAttributes->GetCurrentShield() <= 0 || ActualDamage < 0)
		{
			//ActualDamage = ActualDamage * (1 - (CharacterAttributes->GetPhysicalDefense() / 2000.0f)); //2000 is 100% protection
			CharacterAttributes->SetCurrentHealth(CharacterAttributes->GetCurrentHealth() - ActualDamage);
			if (CharacterAttributes->GetCurrentHealth() <= 0)
			{
				Die(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
			}
			else
			{
				PlayHit(ActualDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
			}
			MakeNoise(1.0f, EventInstigator ? EventInstigator->GetPawn() : this);
		}
	}

	return ActualDamage;*/
	return 0;
}

bool AXLCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	/*if (!SSCharacterCan::Die(this))
	{
		return false;
	}

	CharacterAttributes->SetCurrentHealth(FMath::Min(0.0f, CharacterAttributes->GetCurrentHealth()));

	// if this is an environmental death then refer to the previous killer so that they receive credit (knocked into lava pits, etc)
	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
	Killer = GetDamageInstigator(Killer, *DamageType);

	AController* const KilledPlayer = (Controller != NULL) ? Controller : Cast<AController>(GetOwner());
	GetWorld()->GetAuthGameMode<ASSGameMode>()->Killed(Killer, KilledPlayer, this, DamageType);

	OnDeath(KillingDamage, DamageEvent, Killer ? Killer->GetPawn() : NULL, DamageCauser);*/
	return true;
}

void AXLCharacter::OnDeath(float KillingDamage, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser)
{
	//if (IsDying)
	//{
	//	return;
	//}

	//IsDying = true;

	//PlayHit(KillingDamage, DamageEvent, PawnInstigator, DamageCauser);

	//// cannot use IsLocallyControlled here, because even local client's controller may be NULL here
	//if (CharacterEffects->GetDeathSound() && GetMesh() && GetMesh()->IsVisible())
	//{
	//	UGameplayStatics::PlaySoundAtLocation(this, CharacterEffects->GetDeathSound(), GetActorLocation());
	//}

	//// remove all weapons
	////DestroyInventory();
	//DetachFromControllerPendingDestroy();
	//StopAllAnimMontages();

	///*if (RunLoopAC)
	//{
	//RunLoopAC->Stop();
	//}*/

	//// Death anim
	//float DeathAnimDuration = PlayAnimMontage(CharacterEffects->GetDeathAnim());
	//CharacterWeapon->SetLifeSpan(2.1f);
	//SetLifeSpan(2.1f);
}

void AXLCharacter::PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser)
{
	//// play the force feedback effect on the client player controller
	//APlayerController* PC = Cast<APlayerController>(Controller);
	//if (PC && DamageEvent.DamageTypeClass)
	//{
	//	USSDamageType *DamageType = Cast<USSDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject());
	//	if (DamageType && DamageType->HitForceFeedback)
	//	{
	//		PC->ClientPlayForceFeedback(DamageType->HitForceFeedback, false, "Damage");
	//	}
	//}


	//if (DamageTaken > 0.f)
	//{
	//	//ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	//}
}


float AXLCharacter::PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance)
	{
		return UseMesh->AnimScriptInstance->Montage_Play(AnimMontage, InPlayRate);
	}

	return 0.0f;
}

void AXLCharacter::StopAnimMontage(class UAnimMontage* AnimMontage)
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance &&
		UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
	{
		UseMesh->AnimScriptInstance->Montage_Stop(AnimMontage->BlendOut.GetBlendTime());
	}
}

void AXLCharacter::StopAllAnimMontages()
{
	USkeletalMeshComponent* UseMesh = GetMesh();
	if (UseMesh && UseMesh->AnimScriptInstance)
	{
		UseMesh->AnimScriptInstance->Montage_Stop(0.0f);
	}
}
