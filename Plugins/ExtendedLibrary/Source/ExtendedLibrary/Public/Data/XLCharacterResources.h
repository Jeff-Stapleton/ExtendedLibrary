#pragma once

#include "Components/ActorComponent.h"
#include "XLCharacterResources.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLCharacterResources : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLCharacterResources();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/** The amount of health the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxHealth;
	float CurrentHealth;

	/** The amount of energy the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxEnergy;
	float CurrentEnergy;

	/** The amount of stamina the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxStamina;
	float CurrentStamina;

	/** The amount of Ultimate the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxUltimate;
	float CurrentUltimate;

	/** The amount of shield the Pawn has */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Resources)
	float MaxShield;
	float CurrentShield;
};