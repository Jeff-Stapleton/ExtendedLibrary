#pragma once

#include "XLPickup.generated.h"

// Base class for pickup objects that can be placed in the world
UCLASS(abstract)
class AXLPickup : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Effects)
	class UXLPickupEffectManager* PickupEffects;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class UXLPickupSoundManager* PickupSounds;

	/** is it ready for interactions? */
	UPROPERTY(Transient, ReplicatedUsing = OnRep_IsActive)
	uint32 bIsActive : 1;

protected:

	/** how long it takes to respawn? */
	UPROPERTY(EditDefaultsOnly, Category = Pickup)
	float RespawnTime;

	/* The character who has picked up this pickup */
	UPROPERTY(Transient, Replicated)
	AXLCharacter* PickedUpBy;

	/** Handle for efficient management of RespawnPickup timer */
	FTimerHandle TimerHandle_RespawnPickup;

private:

	/** FX component */
	UPROPERTY(VisibleDefaultsOnly, Category = Effects)
	UParticleSystemComponent* PickupPSC;

protected:

	UFUNCTION()
	void OnRep_IsActive();

	/** give pickup */
	virtual void GivePickupTo(class AXLCharacter* Pawn);

	/** handle touches */
	void PickupOnTouch(class AXLCharacter* Pawn);

	/** show and enable pickup */
	virtual void RespawnPickup();

	/** show effects when pickup disappears */
	virtual void OnPickedUp();

	/** show effects when pickup appears */
	virtual void OnRespawned();

	/** blueprint event: pickup disappears */
	UFUNCTION(BlueprintImplementableEvent)
	void OnPickedUpEvent();

	/** blueprint event: pickup appears */
	UFUNCTION(BlueprintImplementableEvent)
	void OnRespawnEvent();

	/** Returns PickupPSC subobject **/
	FORCEINLINE UParticleSystemComponent* GetPickupPSC() const { return PickupPSC; }

private:

	/** pickup on touch */
	virtual void NotifyActorBeginOverlap(class AActor* Other) override;

	/** initial setup */
	virtual void BeginPlay() override;

};
