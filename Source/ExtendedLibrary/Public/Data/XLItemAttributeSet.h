// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "XLItemAttributeSet.generated.h"

#define ATTIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class EXTENDEDLIBRARY_API UXLItemAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_Damage)
	FGameplayAttributeData Damage;
	ATTIBUTE_ACCESSORS(UXLItemAttributeSet, Damage)

	/** This measures how much damage can be absorbed before dying. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attributes", ReplicatedUsing = OnRep_FOVMultiplier)
	FGameplayAttributeData FOVMultiplier;
	ATTIBUTE_ACCESSORS(UXLItemAttributeSet, FOVMultiplier)

public:

	UXLItemAttributeSet();

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	virtual void OnRep_Damage(const FGameplayAttributeData& OldDamage);

	UFUNCTION()
	virtual void OnRep_FOVMultiplier(const FGameplayAttributeData& OldFOVMultiplier);
};
