#pragma once

#include "ExtendedLibraryPCH.h"

#include "Components/Character/XLMovementComponent.h"
#include "Components/Character/XLInteractionComponent.h"
#include "XLCoverComponent.h"

#include "Enums/XLActionState.h"
#include "Enums/XLCombatState.h"
#include "Enums/XLHealthState.h"
#include "Enums/XLMovementState.h"
#include "Enums/XLPostureState.h"
#include "Enums/XLTargetingState.h"

#include "Managers/XLInventoryManager.h"
#include "Managers/XLAbilityManager.h"
#include "Managers/XLPlayerAnimationManager.h"
#include "XLPlayerEffectManager.h"

#include "Structs/XLHitInfo.h"

#include "XLCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTargetingStateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLookingDelegate);

UCLASS()
class EXTENDEDLIBRARY_API AXLCharacter : public ACharacter
{
	GENERATED_BODY()

public: 

	///////////////////////////////////////////// STATES /////////////////////////////////////////////

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EActionState::Type> ActionState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<ECombatState::Type> CombatState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EHealthState::Type> HealthState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EMovementState::Type> MovementState;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EPostureState::Type> PostureState;

	////////////////////////////////////////////// DATA //////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	class UXLCharacterResources* CharacterResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	class UXLCharacterStats* CharacterStats;

	//////////////////////////////////////////// MANAGERS ////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	class UXLAbilityManager* CharacterAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UXLPlayerAnimationManager* CharacterAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	class UXLPlayerEffectManager* CharacterEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Inventory)
	class UXLInventoryManager* CharacterInventory;


	/////////////////////////////////////////// COMPONENTS ///////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cover)
	class UXLCoverComponent* CoverComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class UXLInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class UXLMovementComponent* MovementComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = Mesh)
	class USkeletalMeshComponent* PerspectiveMesh;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_LastTakeHitInfo)
	struct FXLHitInfo LastHitInfo;

	float LastTakeHitTimeTimeout;

	UPROPERTY(ReplicatedUsing = OnRep_CurrentWeapon, BlueprintReadWrite, Category = Weapons)
	int32 CurrentItem;

	//const int32 UNDEFINED = MAX_int32;

	FLookingDelegate LookingDelegate;

	FTimerDelegate TimerDelegate_SwitchWeapon;
	FTimerHandle TimerHandle_SwitchWeapon;

public: 

	AXLCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OnCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation);

	UFUNCTION(BlueprintCallable, Category = "Camera")
	FRotator AimOffset() const;

	///////////////////////////////////////////// INPUT //////////////////////////////////////////////

	void Move(float Direction);

	void Strafe(float Direction);

	void Turn(float Direction);
	void Look(float Direction);

	void Jump() override;
	void Falling() override;
	void Landed(const FHitResult& Hit) override;

	UFUNCTION(BlueprintCallable, Category = Actions)
	void Interact();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerInteract();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void StartCrouch();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartCrouch();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void StopCrouch();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStopCrouch();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void StartProne();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartProne();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void StopProne();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStopProne();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void StartSprint();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStartSprint();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void StopSprint();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStopSprint();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void EquipItem(int32 Item);
	void HandleEquipItem(int32 Item);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerEquipItem(int32 Item);

	UFUNCTION(BlueprintCallable, Category = Actions)
	float StowItem(int32 Item);
	float HandleStowItem(int32 Item);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerStowItem(int32 Item);

	UFUNCTION(BlueprintCallable, Category = Actions)
	void SwitchItem(int32 NextItem);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSwitchItem(int32 NextItem);

	UFUNCTION(BlueprintCallable, Category = Actions)
	void DropItem(int32 Item);
	void HandleDropItem(int32 Item);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDropItem(int32 Item);

	UFUNCTION(BlueprintCallable, Category = Actions)
	void OnRep_CurrentWeapon(int32 PreviousWeapon);

	UFUNCTION(BlueprintCallable, Category = Actions)
	virtual void StartAim();
	UFUNCTION(BlueprintCallable, Category = Actions)
	virtual void StopAim();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void StartAttack();
	UFUNCTION(BlueprintCallable, Category = Actions)
	void StopAttack();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void Reload();
	UFUNCTION(BlueprintCallable, Category = Actions)
	float Melee();

	UFUNCTION(BlueprintCallable, Category = Actions)
	void StartAbility(int32 Ability);
	UFUNCTION(BlueprintCallable, Category = Actions)
	void StopAbility(int32 Ability);

	///////////////////////////////////////// INITIALIZATION //////////////////////////////////////////

	void SpawnInventory();

	///////////////////////////////////////////// DAMAGE /////////////////////////////////////////////

	UFUNCTION()
	void OnRep_LastTakeHitInfo();

	void ReplicateHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser, bool bKilled);

	float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	bool Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser);

	virtual void OnDeath(float KillingDamage, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser);

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
