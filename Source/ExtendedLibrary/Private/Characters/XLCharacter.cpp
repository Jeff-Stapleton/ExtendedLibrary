
// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Characters/XLCharacter.h"
#include "Cans/XLCharacterCan.h"
#include "Components/Character/XLMovementComponent.h"
#include "Components/Character/XLInteractionComponent.h"
#include "Managers/XLInventoryManager.h"
#include "Items/XLItem.h"
#include "Weapons/XLRangedWeapon.h"
#include "Data/Character/XLCharacterResources.h"
#include "Data/Character/XLCharacterStats.h"
#include "Managers/XLPlayerAnimationManager.h"
#include "Managers/XLPlayerEffectManager.h"
#include "Components/Character/XLCoverComponent.h"


///////////////////////////////////////// INITIALIZATION //////////////////////////////////////////

AXLCharacter::AXLCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXLMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	CharacterResources = CreateDefaultSubobject<UXLCharacterResources>(TEXT("CharacterResources"));
	CharacterStats = CreateDefaultSubobject<UXLCharacterStats>(TEXT("CharacterStats"));
	CharacterInventory = CreateDefaultSubobject<UXLInventoryManager>(TEXT("CharacterInventory"));
	CharacterAnimations = CreateDefaultSubobject<UXLPlayerAnimationManager>(TEXT("CharacterAnimations"));
	CharacterEffects = CreateDefaultSubobject<UXLPlayerEffectManager>(TEXT("CharacterEffects"));
	CoverComponent = CreateDefaultSubobject<UXLCoverComponent>(TEXT("CoverComponent"));
	InteractionComponent = CreateDefaultSubobject<UXLInteractionComponent>(TEXT("InteractionComponent"));
	MovementComponent = Cast<UXLMovementComponent>(GetMovementComponent());

	//GetMesh()->SetAnimInstanceClass(DefaultAnimClass);

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	PrimaryActorTick.bCanEverTick = true;
	MovementComponent->NavAgentProps.bCanCrouch = true;

	ActionState = EActionState::None;
	CombatState = ECombatState::Passive;
	HealthState = EHealthState::Alive;
	MovementState = EMovementState::Idle;
	PostureState = EPostureState::Standing;

	CurrentItem = NULL;

	NetCullDistanceSquared = 225000000.0;
}

void AXLCharacter::BeginPlay()
{
	SpawnInventory();

	Super::BeginPlay();
}

void AXLCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, TEXT("EActionState"), true);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, EnumPtr->GetDisplayNameText(ActionState).ToString());

	if (GetLocalRole() == ROLE_Authority)
	{
		//CharacterResources->Regenerate(DeltaSeconds);
	}

	InteractionComponent->Inspect();
}

void AXLCharacter::OnCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation)
{
	//USkeletalMeshComponent* DefMesh1P = Cast<USkeletalMeshComponent>(GetClass()->GetDefaultSubobjectByName(TEXT("PerspectiveMesh")));
	//const FMatrix DefMeshLS = FRotationTranslationMatrix(DefMesh1P->RelativeRotation, DefMesh1P->RelativeLocation);
	//const FMatrix LocalToWorld = ActorToWorld().ToMatrixWithScale();

	//// Mesh rotating code expect uniform scale in LocalToWorld matrix

	//const FRotator RotCameraPitch(CameraRotation.Pitch, 0.0f, 0.0f);
	//const FRotator RotCameraYaw(0.0f, CameraRotation.Yaw, 0.0f);

	//const FMatrix LeveledCameraLS = FRotationTranslationMatrix(RotCameraYaw, CameraLocation) * LocalToWorld.Inverse();
	//const FMatrix PitchedCameraLS = FRotationMatrix(RotCameraPitch) * LeveledCameraLS;
	//const FMatrix MeshRelativeToCamera = DefMeshLS * LeveledCameraLS.Inverse();
	//const FMatrix PitchedMesh = MeshRelativeToCamera * PitchedCameraLS;

	//PerspectiveMesh->SetRelativeLocationAndRotation(PitchedMesh.GetOrigin(), PitchedMesh.Rotator());
}

void AXLCharacter::SpawnInventory()
{
	if (GetLocalRole() == ROLE_Authority)
	{
		int32 NumWeaponClasses = CharacterInventory->DefaultInventory.Num();
		for (int32 i = 0; i < NumWeaponClasses; i++)
		{
			if (CharacterInventory->DefaultInventory[i])
			{
				FActorSpawnParameters SpawnInfo;
				SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
				AXLItem* NewWeapon = GetWorld()->SpawnActor<AXLItem>(CharacterInventory->DefaultInventory[i], SpawnInfo);

				NewWeapon->SetOwningPawn(this);
				CharacterInventory->Inventory.Add(NewWeapon);
			}
		}
	}
}

void AXLCharacter::Setup()
{

}

//////////////////////////////////////////////////// ACTIONS ////////////////////////////////////////////////////

void AXLCharacter::Move(float Value)
{
	if (XLCharacterCan::Move(this))
	{
		// Limit pitch when walking or falling
		const bool bLimitRotation = (GetCharacterMovement()->IsMovingOnGround() || GetCharacterMovement()->IsFalling());
		const FRotator Rotation = bLimitRotation ? GetActorRotation() : Controller->GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AXLCharacter::Strafe(float Value)
{
	if (XLCharacterCan::Strafe(this))
	{
		const FQuat Rotation = GetActorQuat();
		const FVector Direction = FQuatRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void AXLCharacter::Turn(float Direction)
{
	if (XLCharacterCan::Turn(this))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("PAWN Direction: %f, Rate: %f"), Direction, MovementComponent->BaseTurnRate));
		AddControllerYawInput(Direction * MovementComponent->BaseTurnRate * GetWorld()->GetDeltaSeconds());
		if (FMath::Abs(Direction) > 0.15f)
		{
			LookingDelegate.Broadcast();
		}
	}
}

void AXLCharacter::Look(float Direction)
{
	if (XLCharacterCan::LookUp(this))
	{
		AddControllerPitchInput(Direction * MovementComponent->BaseLookRate * GetWorld()->GetDeltaSeconds());
		// GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("%f"), Direction));
		// Potentially want to only broadcast if the player is currently firing
		if (FMath::Abs(Direction) > 0.15f)
		{
			LookingDelegate.Broadcast();
		}
	}
}

void AXLCharacter::Jump()
{
	if (XLCharacterCan::Jump(this))
	{
		ActionState = EActionState::Jumping;
		Super::Jump();
		MovementComponent->UpdateMovementSpeed();
	}
}
void AXLCharacter::Falling()
{
	PostureState = EPostureState::Airborne;
	Super::Falling();
}
void AXLCharacter::Landed(const FHitResult& Hit)
{
	ActionState = EActionState::None;
	PostureState = EPostureState::Standing;
	Super::Landed(Hit);
}

void AXLCharacter::Interact()
{
	if (XLCharacterCan::StartSprint(this))
	{
		ServerInteract();
		//InteractionComponent->Interact();
	}
}
bool AXLCharacter::ServerInteract_Validate()
{
	return true;
}
void AXLCharacter::ServerInteract_Implementation()
{
	InteractionComponent->Interact();
}

void AXLCharacter::StartCrouch()
{
	if (XLCharacterCan::StartCrouch(this))
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerStartCrouch();
		}

		Crouch();
		PostureState = EPostureState::Crouching;
		MovementComponent->UpdateMovementSpeed();
	}
}
bool AXLCharacter::ServerStartCrouch_Validate()
{
	return true;
}
void AXLCharacter::ServerStartCrouch_Implementation()
{
	StartCrouch();
}

void AXLCharacter::StopCrouch()
{
	if (XLCharacterCan::StopCrouch(this))
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerStopCrouch();
		}

		UnCrouch();
		PostureState = EPostureState::Standing;
		MovementComponent->UpdateMovementSpeed();
	}
}
bool AXLCharacter::ServerStopCrouch_Validate()
{
	return true;
}
void AXLCharacter::ServerStopCrouch_Implementation()
{
	StopCrouch();
}

void AXLCharacter::StartProne()
{
	if (XLCharacterCan::StartProne(this))
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerStartProne();
		}
		PostureState = EPostureState::Prone;
		MovementComponent->UpdateMovementSpeed();
	}
}
bool AXLCharacter::ServerStartProne_Validate()
{
	return true;
}
void AXLCharacter::ServerStartProne_Implementation()
{
	StartProne();
}

void AXLCharacter::StopProne()
{
	if (XLCharacterCan::StopProne(this))
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerStopProne();
		}
		PostureState = EPostureState::Standing;
		MovementComponent->UpdateMovementSpeed();
	}
}
bool AXLCharacter::ServerStopProne_Validate()
{
	return true;
}
void AXLCharacter::ServerStopProne_Implementation()
{
	StopProne();
}

void AXLCharacter::StartSprint()
{
	if (XLCharacterCan::StartSprint(this))
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerStartSprint();
		}
		ActionState = EActionState::Sprinting;
		MovementComponent->UpdateMovementSpeed();
	}
}
bool AXLCharacter::ServerStartSprint_Validate()
{
	return true;
}
void AXLCharacter::ServerStartSprint_Implementation()
{
	StartSprint();
}

void AXLCharacter::StopSprint()
{
	if (XLCharacterCan::StopSprint(this))
	{
		if (GetLocalRole() < ROLE_Authority)
		{
			ServerStopSprint();
		}
		ActionState = EActionState::None;
		MovementComponent->UpdateMovementSpeed();
	}
}
bool AXLCharacter::ServerStopSprint_Validate()
{
	return true;
}
void AXLCharacter::ServerStopSprint_Implementation()
{
	StopSprint();
}

void AXLCharacter::EquipItem(AXLItem* Item, FName Socket)
{
	if (XLCharacterCan::StartEquip(this, Item))
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			HandleEquipItem(Item, Socket);
		}
		else
		{
			ServerEquipItem(Item, Socket);
		}
	}
}
void AXLCharacter::HandleEquipItem(AXLItem* Item, FName Socket)
{
	CurrentItem = Item;
	if (CurrentItem)
	{
		CurrentItem->Equip(Head, "Hand_R");

		CharacterAnimations->SetAnimClass(CurrentItem->AnimClass);
	}
}
bool AXLCharacter::ServerEquipItem_Validate(AXLItem* Item, FName Socket)
{
	return true;
}
void AXLCharacter::ServerEquipItem_Implementation(AXLItem* Item, FName Socket)
{
	EquipItem(Item, Socket);
}

void AXLCharacter::StowItem(AXLItem* Item, USkeletalMeshComponent* AttachedMesh3P, USkeletalMeshComponent* AttachedMesh1P, FName Socket)
{
	if (XLCharacterCan::StopEquip(this))
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			HandleStowItem(Item, AttachedMesh3P, AttachedMesh1P, Socket);
		}
		else
		{
			ServerStowItem(Item, AttachedMesh3P, AttachedMesh1P, Socket);
		}
	}
}
void AXLCharacter::HandleStowItem_Implementation(AXLItem* Item, USkeletalMeshComponent* AttachedMesh3P, USkeletalMeshComponent* AttachedMesh1P, FName Socket)
{
	if (CurrentItem)
	{
		CurrentItem->Equip(AttachedMesh3P, Socket);

		CharacterAnimations->SetAnimClass(CharacterAnimations->DefaultAnimClass);
	}
	CurrentItem = NULL;
}
bool AXLCharacter::ServerStowItem_Validate(AXLItem* Item, USkeletalMeshComponent* AttachedMesh3P, USkeletalMeshComponent* AttachedMesh1P, FName Socket)
{
	return true;
}
void AXLCharacter::ServerStowItem_Implementation(AXLItem* Item, USkeletalMeshComponent* AttachedMesh3P, USkeletalMeshComponent* AttachedMesh1P, FName Socket)
{
	StowItem(Item, AttachedMesh3P, AttachedMesh1P, Socket);
}

void AXLCharacter::SwitchItem(AXLItem* NextItem)
{
	if (XLCharacterCan::StartEquip(this, NextItem))
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			float Duration = CurrentItem->UnequipDuration;
			//StowItem(CurrentItem, "");

			TimerDelegate_SwitchWeapon.BindUFunction(this, FName("EquipItem"), NextItem);
			GetWorldTimerManager().SetTimer(TimerHandle_SwitchWeapon, TimerDelegate_SwitchWeapon, Duration, false);
		}
		else
		{
			ServerSwitchItem(NextItem);
		}
	}
}
bool AXLCharacter::ServerSwitchItem_Validate(AXLItem* NextItem)
{
	return true;
}
void AXLCharacter::ServerSwitchItem_Implementation(AXLItem* NextItem)
{
	SwitchItem(NextItem);
}

void AXLCharacter::DropItem(AXLItem* Item)
{
	if (XLCharacterCan::StopEquip(this))
	{
		if (GetLocalRole() == ROLE_Authority)
		{
			HandleDropItem(Item);
		}
		else
		{
			ServerDropItem(Item);
			//HandleDropItem(Item);
		}
	}
}
void AXLCharacter::HandleDropItem(AXLItem* Item)
{
	// Possible a blueprint event hear to handle dropping specifics
	Item->Drop();
	if (Item == CurrentItem)
	{
		CurrentItem = NULL;
	}
}
bool AXLCharacter::ServerDropItem_Validate(AXLItem* Item)
{
	return true;
}
void AXLCharacter::ServerDropItem_Implementation(AXLItem* Item)
{
	DropItem(Item);
}

void AXLCharacter::OnRep_CurrentWeapon(AXLItem* PreviousWeapon)
{
	if (CurrentItem)
	{
		HandleEquipItem(CurrentItem, "Hand_R");
	}
}

void AXLCharacter::StartAim()
{
	if (XLCharacterCan::StartAim(this))
	{
		AXLRangedWeapon* Weapon = Cast<AXLRangedWeapon>(CurrentItem);
		if (Weapon)
		{
			Weapon->StartAiming();
		}
	}
}
void AXLCharacter::StopAim()
{
	if (XLCharacterCan::StopAim(this))
	{
		AXLRangedWeapon* Weapon = Cast<AXLRangedWeapon>(CurrentItem);
		if (Weapon)
		{
			Weapon->StopAiming();
		}
	}
}

void AXLCharacter::StartAttack()
{
	if (XLCharacterCan::StartAttack(this))
	{
		AXLRangedWeapon* Weapon = Cast<AXLRangedWeapon>(CurrentItem);
		if (Weapon)
		{
			Weapon->StartAttack();
		}
	}
}
void AXLCharacter::StopAttack()
{
	if (XLCharacterCan::StopAttack(this))
	{
		AXLRangedWeapon* Weapon = Cast<AXLRangedWeapon>(CurrentItem);
		if (Weapon)
		{
			Weapon->StopAttack();
		}
	}
}

void AXLCharacter::StartItemPrimaryActivate()
{
	//TODO: Update can method with item equivalent
	if (XLCharacterCan::StartAttack(this))
	{
		if (CurrentItem)
		{
			CurrentItem->PrimaryActivate();
		}
	}
}
void AXLCharacter::StopItemPrimaryActivate()
{
	//TODO: Update can method with item equivalent
	if (XLCharacterCan::StopAttack(this))
	{
		if (CurrentItem)
		{
			CurrentItem->PrimaryDeactivate();
		}
	}
}

void AXLCharacter::StartItemSecondaryActivate()
{
	//TODO: Update can method with item equivalent
	if (XLCharacterCan::StartAttack(this))
	{
		if (CurrentItem)
		{
			CurrentItem->SecondaryActivate();
		}
	}
}
void AXLCharacter::StopItemSecondaryActivate()
{
	//TODO: Update can method with item equivalent
	if (XLCharacterCan::StopAttack(this))
	{
		if (CurrentItem)
		{
			CurrentItem->SecondaryDeactivate();
		}
	}
}

void AXLCharacter::StartItemTertiaryActivate()
{
	if (XLCharacterCan::StartAttack(this))
	{
		if (CurrentItem)
		{
			CurrentItem->TertiaryActivate();
		}
	}
}
void AXLCharacter::StopItemTertiaryActivate()
{
	if (XLCharacterCan::StartAttack(this))
	{
		if (CurrentItem)
		{
			CurrentItem->TertiaryActivate();
		}
	}
}

void AXLCharacter::Reload()
{
	if (XLCharacterCan::StartReload(this))
	{
		AXLRangedWeapon* Weapon = Cast<AXLRangedWeapon>(CurrentItem);
		if (Weapon)
		{
			Weapon->Reload();
		}
	}
}

float AXLCharacter::Melee()
{
	return 0.0f;
	//CharacterWeapon->Melee();
}

void AXLCharacter::StartAbility(int32 Ability)
{
	if (XLCharacterCan::StartAbility(this))
	{
		//CharacterAbilities->ActivateAbility(Ability);
	}
}
void AXLCharacter::StopAbility(int32 Ability)
{
	if (XLCharacterCan::StopAbility(this))
	{
		//CharacterAbilities->DeactivateAbility(Ability);
	}
}

//////////////////////////////////////////////////// DAMAGE /////////////////////////////////////////////////////

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

	DeathDelegate.Broadcast();
	CharacterResources->CurrentHealth = FMath::Min(0.0f, CharacterResources->CurrentHealth);

	// if this is an environmental death then refer to the previous killer so that they receive credit (knocked into lava pits, etc)
	UDamageType const* const DamageType = DamageEvent.DamageTypeClass ? DamageEvent.DamageTypeClass->GetDefaultObject<UDamageType>() : GetDefault<UDamageType>();
	Killer = GetDamageInstigator(Killer, *DamageType);

	AController* const KilledPlayer = (Controller != NULL) ? Controller : Cast<AController>(GetOwner());
	//GetWorld()->GetAuthGameMode<ASSGameMode>()->Killed(Killer, KilledPlayer, this, DamageType);

	NetUpdateFrequency = GetDefault<AXLCharacter>()->NetUpdateFrequency;
	GetCharacterMovement()->ForceReplicationUpdate();

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

	if (GetLocalRole() == ROLE_Authority)
	{
		ReplicateHit(KillingDamage, DamageEvent, PawnInstigator, DamageCauser, true);
	}

	// cannot use IsLocallyControlled here, because even local client's controller may be NULL here
	/*if (CharacterEffects->GetDeathSound() && GetMesh() && GetMesh()->IsVisible())
	{
		UGameplayStatics::PlaySoundAtLocation(this, CharacterEffects->GetDeathSound(), GetActorLocation());
	}*/

	// remove all weapons
	CharacterInventory->DestroyInventory();
	DetachFromControllerPendingDestroy();
	StopAllAnimations();
	// StopAllSounds();

	SetRagdollPhysics();
	const FPointDamageEvent* Temp = (const FPointDamageEvent*)&DamageEvent;

	OnDeathEvent();
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	SetLifeSpan(5.0f);
}

void AXLCharacter::OnRep_LastTakeHitInfo()
{
	if (LastHitInfo.bKilled)
	{
		OnDeath(LastHitInfo.ActualDamage, LastHitInfo.GetDamageEvent(), LastHitInfo.PawnInstigator.Get(), LastHitInfo.DamageCauser.Get());
	}
	else
	{
		PlayHit(LastHitInfo.ActualDamage, LastHitInfo.GetDamageEvent(), LastHitInfo.PawnInstigator.Get(), LastHitInfo.DamageCauser.Get());
	}
}

void AXLCharacter::PlayHit(float DamageTaken, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser)
{
	if (GetLocalRole() == ROLE_Authority)
	{
		ReplicateHit(DamageTaken, DamageEvent, PawnInstigator, DamageCauser, false);
	}
}

void AXLCharacter::ReplicateHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* PawnInstigator, class AActor* DamageCauser, bool bKilled)
{
	const float TimeoutTime = GetWorld()->GetTimeSeconds() + 0.5f;

	FDamageEvent const& LastDamageEvent = LastHitInfo.GetDamageEvent();
	if ((PawnInstigator == LastHitInfo.PawnInstigator.Get()) && (LastDamageEvent.DamageTypeClass == LastHitInfo.DamageTypeClass) && (LastTakeHitTimeTimeout == TimeoutTime))
	{
		// same frame damage
		if (bKilled && LastHitInfo.bKilled)
		{
			// Redundant death take hit, just ignore it
			return;
		}

		// otherwise, accumulate damage done this frame
		Damage += LastHitInfo.ActualDamage;
	}

	LastHitInfo.ActualDamage = Damage;
	LastHitInfo.PawnInstigator = Cast<AXLCharacter>(PawnInstigator);
	LastHitInfo.DamageCauser = DamageCauser;
	LastHitInfo.SetDamageEvent(DamageEvent);
	LastHitInfo.bKilled = HealthState == EHealthState::Dying;
	LastHitInfo.EnsureReplication();

	LastTakeHitTimeTimeout = TimeoutTime;
}

//////////////////////////////////////////////////// HELPERS ////////////////////////////////////////////////////

FRotator AXLCharacter::AimOffset() const
{
	const FVector AimDirWS = GetBaseAimRotation().Vector();
	const FVector AimDirLS = ActorToWorld().InverseTransformVectorNoScale(AimDirWS);
	const FRotator AimRotLS = AimDirLS.Rotation();

	return AimRotLS;
}

void AXLCharacter::SetRagdollPhysics()
{
	bool bInRagdoll = false;

	/*if (IsPendingKill())
	{
		bInRagdoll = false;
	}*/
	if (!Head || !Head->GetPhysicsAsset())
	{
		//bInRagdoll = false;
	}
	else
	{
		Head->SetSimulatePhysics(true);
		Head->WakeAllRigidBodies();
		Head->bBlendPhysics = true;

		UpperBody->SetSimulatePhysics(true);
		UpperBody->WakeAllRigidBodies();
		UpperBody->bBlendPhysics = true;

		LowerBody->SetSimulatePhysics(true);
		LowerBody->WakeAllRigidBodies();
		LowerBody->bBlendPhysics = true;

		Hands->SetSimulatePhysics(true);
		Hands->WakeAllRigidBodies();
		Hands->bBlendPhysics = true;

		Feet->SetSimulatePhysics(true);
		Feet->WakeAllRigidBodies();
		Feet->bBlendPhysics = true;

		bInRagdoll = true;
	}

	//if ((Impact.GetComponent() != nullptr) && Impact.GetComponent()->IsSimulatingPhysics())
	//{
	//	Impact.GetComponent()->AddForce((WeaponStats->Force * ShootDir.Normalize), Impact.BoneName);
	//}

	MovementComponent->StopMovementImmediately();
	MovementComponent->DisableMovement();
	MovementComponent->SetComponentTickEnabled(false);

	if (!bInRagdoll)
	{
		TurnOff();
		SetActorHiddenInGame(true);
		SetLifeSpan(1.0f);
	}
	else
	{
		SetLifeSpan(10.0f);
	}
}

void AXLCharacter::PlayAnimation_Implementation(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		USkeletalMeshComponent* UseMesh = GetMesh();
		if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance)
		{
			UseMesh->AnimScriptInstance->Montage_Play(AnimMontage, InPlayRate);
		}
	}
}

void AXLCharacter::StopAnimation_Implementation(class UAnimMontage* AnimMontage)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		USkeletalMeshComponent* UseMesh = GetMesh();
		if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance &&
			UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
		{
			UseMesh->AnimScriptInstance->Montage_Stop(AnimMontage->BlendOut.GetBlendTime());
		}
	}
}

void AXLCharacter::StopAllAnimations_Implementation()
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		USkeletalMeshComponent* UseMesh = GetMesh();
		if (UseMesh && UseMesh->AnimScriptInstance)
		{
			UseMesh->AnimScriptInstance->Montage_Stop(0.0f);
		}
	}
}

////////////////////////////////////////////////// REPLICATION //////////////////////////////////////////////////

void AXLCharacter::PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker)
{
	Super::PreReplication(ChangedPropertyTracker);

	// Only replicate this property for a short duration after it changes so join in progress players don't get spammed with fx when joining late
	DOREPLIFETIME_ACTIVE_OVERRIDE(AXLCharacter, LastHitInfo, GetWorld() && GetWorld()->GetTimeSeconds() < LastTakeHitTimeTimeout);
}

void AXLCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AXLCharacter, CurrentItem);
	//DOREPLIFETIME(AXLCharacter, HealthState);

	DOREPLIFETIME_CONDITION(AXLCharacter, ActionState, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AXLCharacter, CombatState, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AXLCharacter, MovementState, COND_SkipOwner);
	DOREPLIFETIME_CONDITION(AXLCharacter, PostureState, COND_SkipOwner);

	DOREPLIFETIME_CONDITION(AXLCharacter, LastHitInfo, COND_Custom);
}
