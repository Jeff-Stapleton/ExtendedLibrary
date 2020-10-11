#pragma once

#include "GameFramework/Actor.h"
#include "Enums/XLItemPrimaryState.h"
#include "Enums/XLItemSecondaryState.h"
#include "Structs/XLItemSounds.h"
#include "Structs/XLItemAnimations.h"
#include "XLItem.generated.h"

class AXLPickup;
class AXLAction;
class AXLCharacter;
class USoundCue;
class UParticleSystem;
class UAnimMontage;
class UAnimInstance;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemPrimaryStateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FItemSecondaryStateDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FCharacterDeathDelegate);

UCLASS()
class EXTENDEDLIBRARY_API AXLItem : public AActor
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Item")
	FName Identifier;

	UPROPERTY(BlueprintReadWrite, Category = "XL|Item")
	TArray<TSubclassOf<AXLAction>> ActionBPs;
	UPROPERTY(BlueprintReadWrite, Category = "XL|Item")
	TArray<AXLAction*> Actions;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Item")
	USkeletalMeshComponent* Mesh3P;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Item")
	USkeletalMeshComponent* Mesh1P;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = "IO|Equipment")
	FName Socket;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = "IO|Equipment")
	USkeletalMeshComponent* StowedMesh3P;
	UPROPERTY(Replicated, BlueprintReadWrite, Category = "IO|Equipment")
	USkeletalMeshComponent* StowedMesh1P;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "XL|Item")
	TSubclassOf<UAnimInstance> AnimClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Item")
	int32 MaxCount;
	UPROPERTY(BlueprintReadWrite, Category = "XL|Item")
	int32 Count;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Item")
	float EquipDuration = 2.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Item")
	float UnequipDuration = 2.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Item")
	bool IsToggleActivated;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Item")
	FItemSounds ItemSounds;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Item")
	FItemAnimations ItemAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Item")
	TSubclassOf<AXLPickup> Item_PU;

	UPROPERTY(Transient, ReplicatedUsing = OnRep_MyPawn, BlueprintReadWrite, Category = "XL|Item")
	AXLCharacter* Character;

	UPROPERTY(BlueprintReadWrite, Category = "XL|Item")
	TEnumAsByte<EItemPrimaryState::Type> PrimaryState;

	UPROPERTY(BlueprintReadWrite, Category = "XL|Item")
	TEnumAsByte<EItemSecondaryState::Type> SecondaryState;

	FItemPrimaryStateDelegate ItemPrimaryStateDelegate;
	FItemSecondaryStateDelegate ItemSecondaryStateDelegate;
	FCharacterDeathDelegate CharacterDeathDelegate;
	FTimerHandle TimerHandle_Equip;
	FTimerHandle TimerHandle_Unequip;
	
public:

	AXLItem();

	void PostInitializeComponents() override;

	void Destroyed() override;

	virtual void Tick(float DeltaSeconds) override;

	void SetOwningPawn(AXLCharacter* Character);

	UFUNCTION()
	void OnRep_MyPawn();

	UFUNCTION()
	void OnCharacterDeath();

	virtual void Remove();

	UFUNCTION(Unreliable, Server, WithValidation)
	virtual void PlayFX(UParticleSystem* FX, FName AttachPoint);

	UFUNCTION(Unreliable, Server, WithValidation)
	virtual void PlaySound(USoundCue* Sound);

	UFUNCTION(Unreliable, Server, WithValidation)
	virtual void PlayAnimation(UAnimMontage* Animation, float InPlayRate = 1.f);

	virtual FVector GetSocketLocation(FName SocketName);

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void Equip(USkeletalMeshComponent* AttachMesh3P, FName AttachPoint);

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void Unequip();

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void Drop();

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void PrimaryActivate();
	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void PrimaryDeactivate();

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void SecondaryActivate();
	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void SecondaryDeactivate();

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void TertiaryActivate();
	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void TertiaryDeactivate();

	virtual void TogglePerspective();

protected:

	UFUNCTION(Unreliable, NetMulticast)
	virtual void HandlePlayFX(UParticleSystem* FX, FName AttachPoint);

	UFUNCTION(Unreliable, NetMulticast)
	virtual void HandlePlaySound(USoundCue* Sound);

	UFUNCTION(Unreliable, NetMulticast)
	virtual void HandlePlayAnimation(UAnimMontage* Animation, float InPlayRate = 1.f);

};
