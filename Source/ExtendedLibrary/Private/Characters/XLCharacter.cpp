
// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Action/XLAbilitySystemComponent.h"
#include "Action/XLGameplayAbility.h"
#include "Effects/XLGameplayEffect.h"
#include "Characters/XLCharacter.h"
#include "Cans/XLCharacterCan.h"
#include "Components/Character/XLMovementComponent.h"
#include "Components/Character/XLInteractionComponent.h"
#include "Managers/XLInventoryManager.h"
#include "Items/XLItem.h"
#include "Data/XLCharacterAttributeSet.h"
#include "Weapons/XLRangedWeapon.h"
#include "Data/Character/XLCharacterResources.h"
#include "Data/Character/XLCharacterStats.h"
#include "Managers/XLPlayerAnimationManager.h"
#include "Managers/XLPlayerEffectManager.h"
#include "Components/Character/XLCoverComponent.h"

//////////////////////////////////////////////// INITIALIZATION ///////////////////////////////////////////////////

AXLCharacter::AXLCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UXLMovementComponent>(ACharacter::CharacterMovementComponentName).DoNotCreateDefaultSubobject(ACharacter::MeshComponentName))
{
	AbilitySystemComponent = CreateDefaultSubobject<UXLAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Full);

	CharacterAttributes = CreateDefaultSubobject<UXLCharacterAttributeSet>(TEXT("CharacterAttributes"));
	CharacterResources = CreateDefaultSubobject<UXLCharacterResources>(TEXT("CharacterResources"));
	CharacterStats = CreateDefaultSubobject<UXLCharacterStats>(TEXT("CharacterStats"));
	CharacterInventory = CreateDefaultSubobject<UXLInventoryManager>(TEXT("CharacterInventory"));
	CharacterAnimations = CreateDefaultSubobject<UXLPlayerAnimationManager>(TEXT("CharacterAnimations"));
	CharacterEffects = CreateDefaultSubobject<UXLPlayerEffectManager>(TEXT("CharacterEffects"));
	CoverComponent = CreateDefaultSubobject<UXLCoverComponent>(TEXT("CoverComponent"));
	InteractionComponent = CreateDefaultSubobject<UXLInteractionComponent>(TEXT("InteractionComponent"));
	MovementComponent = Cast<UXLMovementComponent>(GetMovementComponent());

	Head = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Head"));
	UpperBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("UpperBody"));
	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	LowerBody = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("LowerBody"));
	Hands = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Hands"));
	Feet = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Feet"));

	Head->SetupAttachment(GetCapsuleComponent());
	UpperBody->SetupAttachment(GetCapsuleComponent());
	Arms->SetupAttachment(GetCapsuleComponent());
	LowerBody->SetupAttachment(GetCapsuleComponent());
	Hands->SetupAttachment(GetCapsuleComponent());
	Feet->SetupAttachment(GetCapsuleComponent());

	// Ideally we'd adjust the skeletal meshes and not need these
	Head->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Head->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	UpperBody->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	UpperBody->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	Arms->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Arms->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	LowerBody->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	LowerBody->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	Hands->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Hands->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));
	Feet->SetRelativeRotation(FRotator(0.0f, -90.0f, 0.0f));
	Feet->SetRelativeLocation(FVector(0.0f, 0.0f, -96.0f));

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

	bAbilitiesInitialized = false;
}

void AXLCharacter::BeginPlay()
{
	//InitItems();

	Super::BeginPlay();

	check(AbilitySystemComponent);

	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	InitItems();
	InitAbilities();
	InitEffects();

	bAbilitiesInitialized = true;
}

void AXLCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	InteractionComponent->Inspect();

	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Jump Height: %f"), CharacterAttributes->GetJumpHeight()));
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

//////////////////////////////////////////////////// ABILITIES ////////////////////////////////////////////////////

UAbilitySystemComponent * AXLCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AXLCharacter::InitAbilities()
{
	if (HasAuthority())
	{
		for (TSubclassOf<UXLGameplayAbility> Ability : DefaultAbilities)
		{
			AddAbility(Ability);
		}
	}
}

void AXLCharacter::InitEffects()
{
	for (TSubclassOf<UXLGameplayEffect> Effect : DefaultEffects)
	{
		AddEffect(Effect);
	}
}

void AXLCharacter::AddAbility(TSubclassOf<UXLGameplayAbility> Ability)
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		TSubclassOf<UXLGameplayAbility>& AbilityRef = Ability;

		FName Id = AbilityRef.GetDefaultObject()->AbilityId;
		FGameplayAbilitySpecHandle Handle = AbilitySystemComponent->GiveAbility(FGameplayAbilitySpec(AbilityRef, 1, INDEX_NONE, this));
		Abilities.Add(FAbilityKeyPair(Id, Handle));
	}
	else
	{
		ServerAddAbility(Ability);
	}
}
bool AXLCharacter::ServerAddAbility_Validate(TSubclassOf<UXLGameplayAbility> Ability)
{
	return true;
}
void AXLCharacter::ServerAddAbility_Implementation(TSubclassOf<UXLGameplayAbility> Ability)
{
	AddAbility(Ability);
}

void AXLCharacter::RemoveAbility(FName Id)
{
	if (HasAuthority() && AbilitySystemComponent)
	{
		for (FAbilityKeyPair Pair : Abilities)
		{
			if (Pair.Id == Id)
			{
				AbilitySystemComponent->ClearAbility(Pair.AbilityHandle);
			}
		}
	}
	else
	{
		ServerRemoveAbility(Id);
	}
}
bool AXLCharacter::ServerRemoveAbility_Validate(FName Id)
{
	return true;
}
void AXLCharacter::ServerRemoveAbility_Implementation(FName Id)
{
	RemoveAbility(Id);
}

void AXLCharacter::AddEffect(TSubclassOf<UXLGameplayEffect> Effect)
{
	if (!HasAuthority())
	{
		ServerAddEffect(Effect);
	}
	if (AbilitySystemComponent)
	{
		TSubclassOf<UXLGameplayEffect>& EffectRef = Effect;

		FGameplayEffectContextHandle EffectContext = AbilitySystemComponent->MakeEffectContext();
		EffectContext.AddSourceObject(this);

		FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponent->MakeOutgoingSpec(Effect, 1, EffectContext);

		if (EffectSpecHandle.IsValid())
		{
			FName Id = EffectRef.GetDefaultObject()->EffectId;
			FActiveGameplayEffectHandle EffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			Effects.Add(FEffectKeyPair(Id, EffectHandle));
		}
	}
}
bool AXLCharacter::ServerAddEffect_Validate(TSubclassOf<UXLGameplayEffect> Effect)
{
	return true;
}
void AXLCharacter::ServerAddEffect_Implementation(TSubclassOf<UXLGameplayEffect> Effect)
{
	AddEffect(Effect);
}

void AXLCharacter::RemoveEffect(FName Id)
{
	if (!HasAuthority())
	{
		ServerRemoveAbility(Id);
	}
	if (AbilitySystemComponent)
	{
		for (FEffectKeyPair Pair : Effects)
		{
			if (Pair.Id == Id)
			{
				AbilitySystemComponent->RemoveActiveGameplayEffect(Pair.EffectHandle);
			}
		}
	}
}
bool AXLCharacter::ServerRemoveEffect_Validate(FName Id)
{
	return true;
}
void AXLCharacter::ServerRemoveEffect_Implementation(FName Id)
{
	RemoveEffect(Id);
}

void AXLCharacter::ActivateAbilityById(FName Id)
{
	check(AbilitySystemComponent);

	for (FAbilityKeyPair Pair : Abilities)
	{
		if (Pair.Id == Id)
		{
			AbilitySystemComponent->TryActivateAbility(Pair.AbilityHandle);
		}
	}
}

void AXLCharacter::EndAbilityById(FName Id)
{
	check(AbilitySystemComponent);
	
	if (!HasAuthority())
	{
		ServerEndAbilityById(Id);
	}

	for (FAbilityKeyPair Pair : Abilities)
	{
		if (Pair.Id == Id)
		{
			AbilitySystemComponent->CancelAbilityHandle(Pair.AbilityHandle);
		}
	}
}
bool AXLCharacter::ServerEndAbilityById_Validate(FName Id)
{
	return true;
}
void AXLCharacter::ServerEndAbilityById_Implementation(FName Id)
{
	EndAbilityById(Id);
}

//////////////////////////////////////////////////// MOVEMENT /////////////////////////////////////////////////////

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

/////////////////////////////////////////////////// INTERACTION ///////////////////////////////////////////////////

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

//////////////////////////////////////////////////// EQUIPMENT ////////////////////////////////////////////////////

void AXLCharacter::InitItems()
{
	if (HasAuthority())
	{
		for (TSubclassOf<AXLItem> Item : DefaultItems)
		{
			AddItem(Item);
		}
	}
}

void AXLCharacter::AddItem(TSubclassOf<AXLItem> Item)
{
	if (HasAuthority())
	{
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		AXLItem* NewItem = GetWorld()->SpawnActor<AXLItem>(Item, SpawnInfo);

		NewItem->SetOwningPawn(this);
		NewItem->SetVisibility(false, true);
		NewItem->Attach(Head, "Hand_R"); // Override get mesh and make a string num for sockets

		Items.Add(NewItem);
	}
	else
	{
		ServerAddItem(Item);
	}
}
bool AXLCharacter::ServerAddItem_Validate(TSubclassOf<AXLItem> Item)
{
	return true;
}
void AXLCharacter::ServerAddItem_Implementation(TSubclassOf<AXLItem> Item)
{
	AddItem(Item);
}

void AXLCharacter::EquipItem(AXLItem* Item, FName Socket)
{
	if (HasAuthority() && Item)
	{
		CurrentItem = Item;
		for (TSubclassOf<UXLGameplayAbility> Ability : CurrentItem->ItemAbilities)
		{
			AddAbility(Ability);
		}
		for (TSubclassOf<UXLGameplayEffect> Effect : CurrentItem->ItemEffects)
		{
			AddEffect(Effect);
		}
		SetAnimBlueprint(CurrentItem->AnimClass);
		CurrentItem->SetVisibility(true, true);
	}
	else
	{
		ServerEquipItem(Item, Socket);
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
		for (TSubclassOf<UXLGameplayAbility> Ability : CurrentItem->ItemAbilities)
		{
			RemoveAbility(Ability.GetDefaultObject()->AbilityId);
		}
		CurrentItem->Attach(AttachedMesh3P, Socket);
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
			float Duration = 1.0f;//CurrentItem->UnequipDuration;
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
		CurrentItem->SetVisibility(true, true);
		SetAnimBlueprint(CurrentItem->AnimClass);
	}
}

///////////////////////////////////////////////////// DAMAGE //////////////////////////////////////////////////////

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
	//GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
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

		Arms->SetSimulatePhysics(true);
		Arms->WakeAllRigidBodies();
		Arms->bBlendPhysics = true;

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

void AXLCharacter::SetAnimBlueprint(TSubclassOf<UAnimInstance> AnimBlueprint)
{
	Head->SetAnimInstanceClass(AnimBlueprint);
}

bool AXLCharacter::PlayAnimation_Validate(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	return true;
}
void AXLCharacter::PlayAnimation_Implementation(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	HandlePlayAnimation(AnimMontage, InPlayRate, StartSectionName);
}
void AXLCharacter::HandlePlayAnimation_Implementation(class UAnimMontage* AnimMontage, float InPlayRate, FName StartSectionName)
{
	if (GetNetMode() != NM_DedicatedServer)
	{
		USkeletalMeshComponent* UseMesh = Head;
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
		USkeletalMeshComponent* UseMesh = Head;
		if (AnimMontage && UseMesh && UseMesh->AnimScriptInstance && UseMesh->AnimScriptInstance->Montage_IsPlaying(AnimMontage))
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
	DOREPLIFETIME(AXLCharacter, Abilities);
	DOREPLIFETIME(AXLCharacter, Effects);
	DOREPLIFETIME(AXLCharacter, Items);
}
