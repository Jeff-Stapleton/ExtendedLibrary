#pragma once

#include "Characters/XLCharacter.h"
#include "XLPickup.generated.h"

// Base class for pickup objects that can be placed in the world
UCLASS(abstract)
class EXTENDEDLIBRARY_API AXLPickup : public AActor
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Mesh)
	UStaticMeshComponent* Component;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sounds)
	class UXLPickupSoundManager* PickupSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Movement)
	UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Configure)
	bool IsPhysicsEnabled;

	UPROPERTY(BlueprintReadWrite, Transient, ReplicatedUsing = OnRep_IsActive)
	uint32 bIsActive : 1;

	UPROPERTY(Transient, BlueprintReadOnly, Replicated)
	class AXLCharacter* PickedUpBy;

	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void DestroyPickup();
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerDestroyPickup();
	//bool ServerDestroyPickup_Validate();
	//void ServerDestroyPickup_Implementation();

	virtual void OnPickedUp(class AXLCharacter* Pawn);

	virtual void PlaySound();

	UFUNCTION(BlueprintImplementableEvent)
	void OnPickedUpEvent();

	UFUNCTION()
	void OnRep_IsActive();

};
