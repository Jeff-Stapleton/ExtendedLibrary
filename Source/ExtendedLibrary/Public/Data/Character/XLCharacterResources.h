#pragma once

#include "Components/ActorComponent.h"
#include "XLCharacterResources.generated.h"

class AXLCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLCharacterResources : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLCharacterResources();

	AXLCharacter* Character;

	/** The amount of health the Pawn has */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxHealth = 100.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float CurrentHealth;

	/** The amount of time before health starts regenerating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cooldowns)
	float HealthRenerationCooldown;
	float HealthCooldown;

	/** The amount of energy the Pawn has */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxEnergy = 100.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float CurrentEnergy;

	/** The amount of time before energy starts regenerating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cooldowns)
	float EnergyRenerationCooldown;
	float EnergyCooldown;

	/** The amount of stamina the Pawn has */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxStamina = 100.0f;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float CurrentStamina;

	/** The amount of time before stamina starts regenerating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cooldowns)
	float StaminaRenerationCooldown;
	float StaminaCooldown;

	/** The amount of shield the Pawn has */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxShield;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float CurrentShield;

	/** The amount of time before Shield starts regenerating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cooldowns)
	float ShieldRenerationCooldown;
	float ShieldCooldown;

	/** The amount of Ultimate the Pawn has */
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxUltimate;
	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Resources)
	float CurrentUltimate;
	
	void Regenerate(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void RegenerateHealth(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void RegenerateStamina(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void RegenerateEnergy(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void RegenerateShield(float DeltaTime);

	UFUNCTION(BlueprintCallable, Category = Behavior)
	void CooldownTimer(float DeltaTime);
};