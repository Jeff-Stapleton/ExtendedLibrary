// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "XLAbilityEffect.h"
#include "Ability/AbilityEffects/XLEffectOptions.h"
#include "XLBlastEffect.generated.h"

/**
 * 
 */
UCLASS()
class AXLBlastEffect : public AXLAbilityEffect
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blast)
	float MaxDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blast)
	float MinDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blast)
	float DamageFalloff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blast)
	float OutterRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Blast)
	float InnerRadius;

	AXLBlastEffect();

	void Activate(class AXLCharacter* Instigator, class AXLCharacter* Target, FXLEffectOptions* Options = NULL) override;

};
