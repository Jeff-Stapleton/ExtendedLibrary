// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "XLCharacterAttributeSet.generated.h"

class AXLCharacter;
class AXLPlayerController;
class AXLPlayerCameraManager;

#define ATTIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class EXTENDEDLIBRARY_API UXLCharacterAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData MaxHealth;
	ATTIBUTE_ACCESSORS(UXLCharacterAttributeSet, MaxHealth)

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Health)
	FGameplayAttributeData Health;
	ATTIBUTE_ACCESSORS(UXLCharacterAttributeSet, Health)

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;
	ATTIBUTE_ACCESSORS(UXLCharacterAttributeSet, MovementSpeed)

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_JumpVelocity)
	FGameplayAttributeData JumpVelocity;
	ATTIBUTE_ACCESSORS(UXLCharacterAttributeSet, JumpVelocity)


	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_VolumeMultiplier)
	FGameplayAttributeData VolumeMultiplier;
	ATTIBUTE_ACCESSORS(UXLCharacterAttributeSet, VolumeMultiplier)

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTIBUTE_ACCESSORS(UXLCharacterAttributeSet, Damage)

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_FOVMultiplier)
	FGameplayAttributeData FOVMultiplier;
	ATTIBUTE_ACCESSORS(UXLCharacterAttributeSet, FOVMultiplier)

private:

	AXLCharacter* Character;
	AXLPlayerController* Controller;
	AXLPlayerCameraManager* CameraManager;

public:
	/** Set default values. For example, Health should be set to a positive number */
	UXLCharacterAttributeSet();

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);

	UFUNCTION()
	virtual void OnRep_Health(const FGameplayAttributeData& OldHealth);

	UFUNCTION()
	virtual void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);

	UFUNCTION()
	virtual void OnRep_JumpVelocity(const FGameplayAttributeData& OldJumpVelocity);

	UFUNCTION()
	virtual void OnRep_VolumeMultiplier(const FGameplayAttributeData& OldVolumeMultiplier);

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldDamage);

	UFUNCTION()
	virtual void OnRep_FOVMultiplier(const FGameplayAttributeData& OldFOVMultiplier);
};
