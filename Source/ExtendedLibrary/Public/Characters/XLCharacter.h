#pragma once

#include "GameFramework/Character.h"
#include "Abilities/GameplayAbility.h"
#include "AbilitySystemInterface.h"
#include "GameplayEffectTypes.h"
#include "GameplayEffect.h"

#include "Enums/XLActionState.h"
#include "Enums/XLCombatState.h"
#include "Enums/XLHealthState.h"
#include "Enums/XLMovementState.h"
#include "Enums/XLPostureState.h"
#include "Enums/XLTargetingState.h"

#include "Structs/XLHitInfo.h"
#include "Structs/XLAbilityKeyPair.h"
#include "Structs/XLEffectKeyPair.h"

#include "XLCharacter.generated.h"

class AXLItem;
class UXLGameplayAbility;
class UXLGameplayEffect;
class UXLAbilitySystemComponent;
class UXLCharacterResources;
class UXLCharacterAttributeSet;
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
class EXTENDEDLIBRARY_API AXLCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public: 

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XL|Character")
	TSubclassOf<UAnimInstance> DefaultAnimClass;

	///////////////////////////////////////////// STATES /////////////////////////////////////////////

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<EActionState::Type> ActionState;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<ECombatState::Type> CombatState;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<EHealthState::Type> HealthState;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<EMovementState::Type> MovementState;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Character")
	TEnumAsByte<EPostureState::Type> PostureState;

	////////////////////////////////////////////// DATA //////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, Category = "XL|Character")
	UXLAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Character")
	UXLCharacterAttributeSet* CharacterAttributes;

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
	USkeletalMeshComponent* Arms;

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

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Character")
	TArray<FAbilityKeyPair> Abilities;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Character")
	TArray<FEffectKeyPair> Effects;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "XL|Character")
	TArray<AXLItem*> Items;

	UPROPERTY()
	bool bAbilitiesInitialized;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "XL|Character")
	TArray<TSubclassOf<UXLGameplayAbility>> DefaultAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "XL|Character")
	TArray<TSubclassOf<UXLGameplayEffect>> DefaultEffects;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "XL|Character")
	TArray<TSubclassOf<AXLItem>> DefaultItems;

	FDeathDelegate DeathDelegate;
	FLookingDelegate LookingDelegate;
	FTimerDelegate TimerDelegate_SwitchWeapon;
	FTimerHandle TimerHandle_SwitchWeapon;

public: 

	/////////////////////////////////////////////// INITIALIZATION ////////////////////////////////////////////////////

	AXLCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	void OnCameraUpdate(const FVector& CameraLocation, const FRotator& CameraRotation);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	FRotator AimOffset() const;

	//////////////////////////////////////////////////// ABILITIES ////////////////////////////////////////////////////

	virtual class UAbilitySystemComponent* GetAbilitySystemComponent() const override;

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void InitAbilities();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void InitEffects();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void AddAbility(TSubclassOf<UXLGameplayAbility> Ability);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerAddAbility(TSubclassOf<UXLGameplayAbility> Ability);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void RemoveAbility(FName Id);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerRemoveAbility(FName Id);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void AddEffect(TSubclassOf<UXLGameplayEffect> Effect);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerAddEffect(TSubclassOf<UXLGameplayEffect> Effect);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void RemoveEffect(FName Id);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerRemoveEffect(FName Id);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void ActivateAbilityById(FName Id);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void EndAbilityById(FName Id);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerEndAbilityById(FName Id);

	/////////////////////////////////////////////////// INTERACTION ///////////////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void Interact();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerInteract();

	//////////////////////////////////////////////////// MOVEMENT /////////////////////////////////////////////////////

	void Move(float Direction);
	void Strafe(float Direction);

	void Turn(float Direction);
	void Look(float Direction);

	//////////////////////////////////////////////////// EQUIPMENT ////////////////////////////////////////////////////

	void InitItems();

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void AddItem(TSubclassOf<AXLItem> Item);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerAddItem(TSubclassOf<AXLItem> Item);

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void EquipItem(AXLItem* Item, FName Socket);
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

	///////////////////////////////////////////// DAMAGE /////////////////////////////////////////////

	UFUNCTION()
	void OnRep_LastTakeHitInfo();

	virtual float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	void ReplicateHit(float Damage, struct FDamageEvent const& DamageEvent, class APawn* InstigatingPawn, class AActor* DamageCauser, bool bKilled);

	void PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser);

	UFUNCTION(BlueprintImplementableEvent)
	void OnDeathEvent();

	bool Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser);

	virtual void OnDeath(float KillingDamage, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser);
		
	void SetRagdollPhysics();

	/////////////////////////////////////////// ANIMATION ///////////////////////////////////////////

	UFUNCTION(BlueprintCallable, Category = "XL|Character")
	void SetAnimBlueprint(TSubclassOf<UAnimInstance> AnimBlueprint);

	UFUNCTION(Unreliable, Server, WithValidation)
	void PlayAnimation(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

	UFUNCTION(Reliable, NetMulticast)
	void StopAnimation(class UAnimMontage* AnimMontage);

	UFUNCTION(Reliable, NetMulticast)
	void StopAllAnimations();

	////////////////////////////////////////// REPLICATION //////////////////////////////////////////

	virtual void PreReplication(IRepChangedPropertyTracker & ChangedPropertyTracker) override;

protected:

	UFUNCTION(Unreliable, NetMulticast)
	virtual void HandlePlayAnimation(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None);

};
