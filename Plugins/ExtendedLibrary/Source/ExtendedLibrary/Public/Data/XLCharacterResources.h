#pragma once

#include "Components/ActorComponent.h"
#include "XLCharacter.h"
#include "XLCharacterResources.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLCharacterResources : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLCharacterResources();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	class AXLCharacter* Character;

	/** The amount of health the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxHealth = 100.0f;
	float CurrentHealth;

	/** The amount of time before health starts regenerating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cooldowns)
	float HealthRenerationCooldown;
	float HealthCooldown;

	/** The amount of energy the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxEnergy = 100.0f;
	float CurrentEnergy;

	/** The amount of time before energy starts regenerating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cooldowns)
	float EnergyRenerationCooldown;
	float EnergyCooldown;

	/** The amount of stamina the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxStamina = 100.0f;
	float CurrentStamina;

	/** The amount of time before stamina starts regenerating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cooldowns)
	float StaminaRenerationCooldown;
	float StaminaCooldown;

	/** The amount of shield the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxShield;
	float CurrentShield;

	/** The amount of time before Shield starts regenerating */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Cooldowns)
	float ShieldRenerationCooldown;
	float ShieldCooldown;

	/** The amount of Ultimate the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxUltimate;
	float CurrentUltimate;
	
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