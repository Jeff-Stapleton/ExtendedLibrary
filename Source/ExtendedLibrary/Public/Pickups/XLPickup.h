#pragma once

#include "Characters/XLCharacter.h"
#include "Managers/XLPickupSoundManager.h"
#include "XLPickup.generated.h"

class UXLPickupSoundManager;
class UProjectileMovementComponent;
class AXLCharacter;

// Base class for pickup objects that can be placed in the world
UCLASS(abstract)
class EXTENDEDLIBRARY_API AXLPickup : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Pickup)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(VisibleDefaultsOnly, Category = Effects)
	UParticleSystemComponent* PickupPSC;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* ActiveFX;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	UParticleSystem* RespawningFX;

	FTimerHandle TimerHandle_RespawnPickup;

	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	float RespawnTime;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	UXLPickupSoundManager* PickupSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Configure)
	bool IsPhysicsEnabled;

	UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing = OnRep_IsActive)
	bool bIsActive;

	UPROPERTY(Transient, BlueprintReadOnly, Replicated)
	AXLCharacter* PickedUpBy;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

	virtual void BeginPlay() override;

	void InitVelocity(FVector& ShootDirection);

	UFUNCTION()
	virtual void PickedUp(AXLCharacter* Pawn);

	UFUNCTION()
	void OnPickedUp();

	UFUNCTION(BlueprintCallable)
	void DestroyPickup();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDestroyPickup();

	UFUNCTION()
	virtual void Respawn();

	UFUNCTION()
	virtual void OnRespawn();

	UFUNCTION()
	void OnRep_IsActive();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickedUpEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void OnRespawnEvent();

	UFUNCTION(BlueprintImplementableEvent)
	void IsActiveChangedEvent();

};
