#pragma once

#include "GameFramework/Actor.h"
#include "Effects/XLGameplayEffect.h"
#include "Enums/XLItemPrimaryState.h"
#include "Enums/XLItemSecondaryState.h"
#include "Structs/XLItemSounds.h"
#include "Structs/XLItemAnimations.h"
#include "XLItem.generated.h"

class AXLPickup;
class UXLGameplayAbility;
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "XL|Item")
	TArray<TSubclassOf<UXLGameplayAbility>> ItemAbilities;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "XL|Item")
	TArray<TSubclassOf<UXLGameplayEffect>> ItemEffects;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "IO|Equipment")
	USceneComponent* Root;
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

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	void SetOwningPawn(AXLCharacter* NewOwner);

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
	virtual void Attach(USkeletalMeshComponent* AttachMesh3P, FName AttachPoint);


	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void SetVisibility(bool Visibility, bool Include1PMesh);
	UFUNCTION(Reliable, NetMulticast, Category = "XL|Item")
	virtual void ServerSetVisibility(bool Visibility, bool Include1PMesh);

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void Detach();

	virtual void Equip();

	virtual void Unequip();

	UFUNCTION(BlueprintCallable, Category = "XL|Item")
	virtual void Drop();

	virtual void TogglePerspective();

protected:

	UFUNCTION(Unreliable, NetMulticast)
	virtual void HandlePlayFX(UParticleSystem* FX, FName AttachPoint);

	UFUNCTION(Unreliable, NetMulticast)
	virtual void HandlePlaySound(USoundCue* Sound);

	UFUNCTION(Unreliable, NetMulticast)
	virtual void HandlePlayAnimation(UAnimMontage* Animation, float InPlayRate = 1.f);

};
