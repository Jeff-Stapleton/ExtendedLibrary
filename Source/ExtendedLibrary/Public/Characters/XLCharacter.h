#pragma once

#include "GameFramework/Character.h"

#include "Enums/XLActionState.h"
#include "Enums/XLCombatState.h"
#include "Enums/XLHealthState.h"
#include "Enums/XLMovementState.h"
#include "Enums/XLPostureState.h"
#include "Enums/XLTargetingState.h"

#include "Structs/XLHitInfo.h"

#include "XLCharacter.generated.h"

class AXLItem;
class UXLCharacterResources;
class UXLCharacterStats;
class UXLAbilityManager;
class UXLPlayerAnimationManager;
class UXLPlayerEffectManager;
class UXLInventoryManager;
class UXLCoverComponent;
class UXLInteractionComponent;
class UXLMovementComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetingStateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLookingDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDeathDelegate);

UCLASS()
class EXTENDEDLIBRARY_API AXLCharacter : public ACharacter
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XL|Character")
	TSubclassOf<UAnimInstance> DefaultAnimClass;

	///////////////////////////////////////////// STATES /////////////////////////////////////////////

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<EActionState::Type> ActionState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<ECombatState::Type> CombatState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<EHealthState::Type> HealthState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<EMovementState::Type> MovementState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<EPostureState::Type> PostureState;

	////////////////////////////////////////////// DATA //////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLCharacterResources* CharacterResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLCharacterStats* CharacterStats;

	//////////////////////////////////////////// MANAGERS ////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLPlayerAnimationManager* CharacterAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLPlayerEffectManager* CharacterEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLInventoryManager* CharacterInventory;

	/////////////////////////////////////////// COMPONENTS ///////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLCoverComponent* CoverComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Head;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* UpperBody;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* LowerBody;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Hands;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	USkeletalMeshComponent* Feet;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_LastTakeHitInfo)
	struct FXLHitInfo LastHitInfo;

	float LastTakeHitTimeTimeout;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_CurrentWeapon, BlueprintReadWrite, Category = Weapons)
	AXLItem* CurrentItem;

	//const int32 UNDEFINED = MAX_int32;

	FDeathDelegate DeathDelegate;
	FLookingDelegate LookingDelegate;
	FTimerDelegate TimerDelegate_SwitchWeapon;
	FTimerHandle TimerHandle_SwitchWeapon;

public: 

	AXLCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OnCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	FRotator AimOffset() const;

	///////////////////////////////////////////// INPUT //////////////////////////////////////////////

	void Move(float Direction);

	void Strafe(float Direction);

	void Turn(float Direction);
	void Look(float Direction);

	void Jump() override;
	void Falling() override;
	void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void Interact();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerInteract();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StartCrouch();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartCrouch();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StopCrouch();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStopCrouch();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StartProne();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartProne();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StopProne();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStopProne();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StartSprint();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartSprint();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StopSprint();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStopSprint();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void EquipItem(AXLItem* Item, FName Socket);
	void HandleEquipItem(AXLItem* Item, FName Socket);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerEquipItem(AXLItem* Item, FName Socket);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StowItem(AXLItem* Item, USkeletalMeshComponent* AttachedMesh3P, USkeletalMeshComponent* AttachedMesh1P, FName Socket);
	UFUNCTION(Reliable, NetMulticast)
	void HandleStowItem(AXLItem* Item, USkeletalMeshComponent* AttachedMesh3P, USkeletalMeshComponent* AttachedMesh1P, FName Socket);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStowItem(AXLItem* Item, USkeletalMeshComponent* AttachedMesh3P, USkeletalMeshComponent* AttachedMesh1P, FName Socket);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void SwitchItem(AXLItem* NextItem);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSwitchItem(AXLItem* NextItem);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void DropItem(AXLItem* Item);
	void HandleDropItem(AXLItem* Item);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDropItem(AXLItem* Item);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void OnRep_CurrentWeapon(AXLItem* PreviousWeapon);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	virtual void StartAim(); //TODO: Delete this method -- Item paradigm is the future
	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	virtual void StopAim(); //TODO: Delete this method -- Item paradigm is the future

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StartAttack(); //TODO: Delete this method -- Item paradigm is the future
	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StopAttack(); //TODO: Delete this method -- Item paradigm is the future

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StartItemPrimaryActivate();
	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StopItemPrimaryActivate();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StartItemSecondaryActivate();
	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StopItemSecondaryActivate();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StartItemTertiaryActivate();
	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StopItemTertiaryActivate();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void Reload();
	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	float Melee();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StartAbility(int32 Ability);
	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void StopAbility(int32 Ability);

	///////////////////////////////////////// INITIALIZATION //////////////////////////////////////////

	void Setup();

	void SpawnInventory();

	///////////////////////////////////////////// DAMAGE /////////////////////////////////////////////

	UFUNCTION()
	void OnRep_LastTakeHitInfo();

	void ReplicateHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser, bool bKilled);

	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	bool Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser);

	virtual void OnDeath(float KillingDamage, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathEvent();
	
	void PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser);

	void SetRagdollPhysics();

	/////////////////////////////////////////// ANIMATION ///////////////////////////////////////////

	UFUNCTION(Reliable, NetMulticast)
	void PlayAnimation(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

	UFUNCTION(Reliable, NetMulticast)
	void StopAnimation(class UAnimMontage* AnimMontage);

	UFUNCTION(Reliable, NetMulticast)
	void StopAllAnimations();

	////////////////////////////////////////// REPLICATION //////////////////////////////////////////

	virtual void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker) override;

};
