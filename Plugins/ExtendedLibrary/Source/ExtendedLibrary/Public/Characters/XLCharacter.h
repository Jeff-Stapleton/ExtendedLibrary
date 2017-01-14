#pragma once

#include "Components/XLMovementComponent.h"
#include "Enums/XLActionState.h"
#include "Enums/XLCombatState.h"
#include "Enums/XLHealthState.h"
#include "Enums/XLMovementState.h"
#include "Enums/XLPostureState.h"
#include "GameFramework/Character.h"
#include "Managers/XLAbilityManager.h"

#include "XLCharacter.generated.h"

UCLASS()
class AXLCharacter : public ACharacter
{
	GENERATED_BODY()

public: 

	///////////////////////////////////////////// STATES /////////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, Category = State)
	TEnumAsByte<EActionState::Type> ActionState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<ECombatState::Type> CombatState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EHealthState::Type> HealthState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EMovementState::Type> MovementState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = State)
	TEnumAsByte<EPostureState::Type> PostureState;

	////////////////////////////////////////// COMPONENTS //////////////////////////////////////////

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	class UXLCharacterResources* CharacterResources;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Stats)
	class UXLCharacterStats* CharacterStats;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapons)
	class UXLWeaponManager* CharacterWeapons;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	class UXLAbilityManager* CharacterAbilities;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	class UXLPlayerAnimationManager* CharacterAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	class UXLPlayerEffectManager* CharacterEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cover)
	class UXLCoverComponent* CoverComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	class UXLMovementComponent* MovementComponent;

public: 

	AXLCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	////////////////////////////////////////////// INPUT //////////////////////////////////////////////

	void Move(float Direction);

	void Strafe(float Direction);

	void Turn(float Direction);
	void Look(float Direction);

	void Jump() override;

	void Landed(const FHitResult& Hit) override;

	void StartSprint();
	void StopSprint();

	void StartAttack();
	void StopAttack();

	void Reload();

	void Melee();

	void StartAbility(int32 Ability);
	void StopAbility(int32 Ability);

	///////////////////////////////////////////// DAMAGE /////////////////////////////////////////////

	float TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser);

	bool Die(float KillingDamage, FDamageEvent const & DamageEvent, AController * Killer, AActor * DamageCauser);

	void OnDeath(float KillingDamage, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser);

	void PlayHit(float DamageTaken, FDamageEvent const & DamageEvent, APawn * PawnInstigator, AActor * DamageCauser);

	/////////////////////////////////////////// ANIMATION ///////////////////////////////////////////

	virtual float PlayAnimMontage(class UAnimMontage* AnimMontage, float InPlayRate = 1.f, FName StartSectionName = NAME_None) override;

	virtual void StopAnimMontage(class UAnimMontage* AnimMontage) override;

	void StopAllAnimMontages();

	////////////////////////////////////////// REPLICATION //////////////////////////////////////////

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetActionState(EActionState::Type State);
	void SetActionState(EActionState::Type State);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetCombatState(ECombatState::Type State);
	void SetCombatState(ECombatState::Type State);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetHealthState(EHealthState::Type State);
	void SetHealthState(EHealthState::Type State);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetMovementState(EMovementState::Type State);
	void SetMovementState(EMovementState::Type State);

	UFUNCTION(Reliable, Server, WithValidation)
	void ServerSetPostureState(EPostureState::Type State);
	void SetPostureState(EPostureState::Type State);
};
