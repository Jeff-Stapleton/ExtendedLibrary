// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLCharacter.h"

AXLCharacter::AXLCharacter()
{
	CharacterResources = CreateDefaultSubobject<UXLCharacterResources>(TEXT("CharacterResources"));
	CharacterStats = CreateDefaultSubobject<UXLCharacterStats>(TEXT("CharacterStats"));
	CharacterWeapons = CreateDefaultSubobject<UXLWeaponManager>(TEXT("CharacterWeapons"));
	CharacterAbilities = CreateDefaultSubobject<UXLAbilityManager>(TEXT("CharacterAbilities"));
	CharacterAnimations = CreateDefaultSubobject<UXLPlayerAnimationManager>(TEXT("CharacterAnimations"));
	CharacterEffects = CreateDefaultSubobject<UXLPlayerEffectManager>(TEXT("CharacterEffects"));
	CoverComponent = CreateDefaultSubobject<UXLCoverComponent>(TEXT("CoverComponent"));
	MovementComponent = Cast<UXLMovementComponent>(GetCharacterMovement());

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	//GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 400.f;
	GetCharacterMovement()->MaxWalkSpeed = 400.f;
	GetCharacterMovement()->AirControl = 0.2f;

	PrimaryActorTick.bCanEverTick = true;

	HealthState = EHealthState::Alive;
	MovementState = EMovementState::Idle;
	CombatState = ECombatState::Passive;
}

void AXLCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AXLCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}


void AXLCharacter::Move(float Value)
{
	if (XLCharacterCan::Move(this))
	{
		//Velocity = Value;

		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AXLCharacter::Strafe(float Value)
{
	if (XLCharacterCan::Strafe(this))
	{
		//Direction = Value;

		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}

void AXLCharacter::Turn(float Direction)
{
	AXLPlayerController* MyPC = Cast<AXLPlayerController>(Controller);
	if (XLCharacterCan::Turn(this))
	{
		AddControllerYawInput(Direction * 45.0f/*turn rate*/ * GetWorld()->GetDeltaSeconds());
	}
}

void AXLCharacter::Look(float Direction)
{
	AXLPlayerController* MyPC = Cast<AXLPlayerController>(Controller);
	if (XLCharacterCan::LookUp(this))
	{
		AddControllerPitchInput(Direction * 45.0f/*turn rate*/ * GetWorld()->GetDeltaSeconds());
	}
}

void AXLCharacter::StartSprint()
{
	if (XLCharacterCan::StartSprint(this))
	{
		MovementState = EMovementState::Sprinting;
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed * 2;
	}
}
void AXLCharacter::StopSprint()
{
	if (XLCharacterCan::StopSprint(this))
	{
		MovementState = EMovementState::Idle;
		GetCharacterMovement()->MaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed / 2;
	}
}

void AXLCharacter::StartAttack()
{
	//CharacterWeapon->StartAttack();
}
void AXLCharacter::StopAttack()
{
	//CharacterWeapon->StopAttack();
}

void AXLCharacter::Reload()
{
	//CharacterWeapon->Reload();
}

void AXLCharacter::Melee()
{
	//CharacterWeapon->Melee();
}


float AXLCharacter::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, class AActor* DamageCauser)
{
	AXLPlayerController* MyPC = Cast<AXLPlayerController>(Controller);
	if (CharacterResources->CurrentHealth <= 0.f)
	{
		return 0.f;
	}

	float ActualDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	if (CharacterResources->CurrentShield > 0)
	{
		float temp = ActualDamage - CharacterResources->CurrentShield;
		CharacterResources->CurrentShield = CharacterResources->CurrentShield - ActualDamage;
		if (temp > 0)
		{
			ActualDamage = temp;
		}
	}
	else
	{
		//Need to check armor and reduce damage accordingly based on damage type.
		CharacterResources->CurrentHealth = CharacterResources->CurrentHealth - ActualDamage;
		if (CharacterResources->CurrentHealth <= 0)
		{
			Die(ActualDamage, DamageEvent, EventInstigator, DamageCauser);
		}
		else
		{
			PlayHit(ActualDamage, DamageEvent, EventInstigator ? EventInstigator->GetPawn() : NULL, DamageCauser);
		}
		MakeNoise(1.0f, EventInstigator ? EventInstigator->GetPawn() : this);
	}
	return ActualDamage;
}

bool AXLCharacter::Die(float KillingDamage, FDamageEvent const& DamageEvent, AController* Killer, AActor* DamageCauser)
{
	if (!XLCharacterCan::Die(this))
	{
		return false;
	}

	CharacterResources->CurrentHealth = FMath::Min(0.0f, CharacterResources->CurrentHealth);

	// if this is an environmental death then refer to the previous killer so that they receive credit (knocked into lava pits, etc)
	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
	Killer = GetDamageInstigator(Killer, *DamageType);

	AController* const KilledPlayer = (Controller != NULL) ? Controller : Cast<AController>(GetOwner());
	//GetWorld()->GetAuthGameMode<ASSGameMode>()->Killed(Killer, KilledPlayer, this, DamageType);

	OnDeath(KillingDamage, DamageEvent, Killer ? Killer->GetPawn() : NULL, DamageCauser);
	return true;
}

void AXLCharacter::OnDeath(float KillingDamage, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser)
{
	if (HealthState == EHealthState::Dying)
	{
		return;
	}

	HealthState = EHealthState::Dying;
	PlayHit(KillingDamage, DamageEvent, PawnInstigator, DamageCauser);

	// cannot use IsLocallyControlled here, because even local client's controller may be NULL here
	/*if (CharacterEffects->GetDeathSound() && GetMesh() && GetMesh()->IsVisible())
	{
		UGameplayStatics::PlaySoundAtLocation(this, CharacterEffects->GetDeathSound(), GetActorLocation());
	}*/

	// remove all weapons
	//DestroyInventory();
	DetachFromControllerPendingDestroy();
	StopAllAnimMontages();

	/*if (RunLoopAC)
	{
	RunLoopAC->Stop();
	}*/

	// Death anim
	float DeathAnimDuration = 2.0f;
	if (CharacterAnimations->DeathAnim)
	{
		DeathAnimDuration = PlayAnimMontage(CharacterAnimations->DeathAnim);
	}
	//CharacterWeapon->SetLifeSpan(2.1f);
	SetLifeSpan(DeathAnimDuration * 0.7f);
}

void AXLCharacter::PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser)
{
	// play the force feedback effect on the client player controller
	APlayerController* PC = Cast<APlayerController>(Controller);
	if (PC && DamageEvent.DamageTypeClass)
	{
		/*USSDamageType *DamageType = Cast<USSDamageType>(DamageEvent.DamageTypeClass->GetDefaultObject());
		if (DamageType && DamageType->HitForceFeedback)
		{
			PC->ClientPlayForceFeedback(DamageType->HitForceFeedback, false, "Damage");
		}*/
	}


	if (DamageTaken > 0.f)
	{
		//ApplyDamageMomentum(DamageTaken, DamageEvent, PawnInstigator, DamageCauser);
	}
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
