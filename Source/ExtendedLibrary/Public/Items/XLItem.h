#pragma once

#include "GameFramework/Actor.h"
#include "Pickups/XLPickup.h"
#include "XLItemSoundManager.h"
#include "XLItemAnimationManager.h"
#include "XLItem.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLItem : public AActor
{
	GENERATED_BODY()
	
public:
	AXLItem();

	void PostInitializeComponents() override;

	void Destroyed() override;

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(Reliable, NetMulticast)
	virtual void PlaySound(USoundCue* Sound);
	UFUNCTION(Reliable, NetMulticast)
	virtual void StopSound();

	UFUNCTION(Reliable, NetMulticast)
	virtual void PlayAnimation(class UAnimMontage* Animation, float InPlayRate = 1.f);
	UFUNCTION(Reliable, NetMulticast)
	virtual void StopAnimation(class UAnimMontage* Animation);

	virtual void AttachMeshToPawn();
	virtual void DetachMeshFromPawn();

	UFUNCTION(Reliable, NetMulticast)
	void PlayFX(UParticleSystem* FX, FName AttachPoint);

	UFUNCTION(Reliable, NetMulticast)
	void StopFX();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	virtual float StartEquip(FName AttachPoint);
	virtual void StopEquip();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	virtual float StartUnequip();
	virtual void StopUnequip();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	virtual void Drop();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	virtual void Activate();
	virtual void Deactivate();

	virtual void TogglePerspective();

	UPROPERTY()
	class AXLCharacter* Character;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Config)
	TSubclassOf<class AXLPickup> Item_PU;

	/* The AnimBlueprint class to use. Use 'SetAnimInstanceClass' to change at runtime. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Animation)
	class TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh3P;
	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Sound)
	class UXLItemSoundManager* ItemSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animations)
	class UXLItemAnimationManager* ItemAnimations;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float EquipDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float UnequipDuration = 2.0f;

	UPROPERTY()
	FName AttachPoint;

	UParticleSystemComponent* FXComponent;
	UAudioComponent* AudioComponent;

	FTimerHandle TimerHandle_Equip;
	FTimerHandle TimerHandle_Unequip;

};