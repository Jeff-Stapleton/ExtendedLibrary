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

	virtual UAudioComponent* PlaySound(USoundCue* Sound);

	virtual float PlayAnimation(class UAnimMontage* Animation, float InPlayRate = 1.f);
	virtual void StopAnimation(class UAnimMontage* Animation);

	virtual void PlayFX();
	virtual void StopFX();

	virtual void AttachMeshToPawn();
	virtual void DetachMeshFromPawn();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	virtual float StartEquip(FName AttachPoint);
	virtual void StopEquip();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	virtual float StartUnequip();
	virtual void StopUnequip();

	UFUNCTION(BlueprintCallable, Category = "Utility")
	virtual void Drop();

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

	UPROPERTY()
	FName AttachPoint;

	FTimerHandle TimerHandle_Equip;
	FTimerHandle TimerHandle_Unequip;

};