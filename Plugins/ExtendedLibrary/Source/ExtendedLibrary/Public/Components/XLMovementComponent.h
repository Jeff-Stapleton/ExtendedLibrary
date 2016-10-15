#pragma once

#include "XLMovementComponent.generated.h"

UCLASS()
class UXLMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	UXLMovementComponent();

public:

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float SprintCost;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float JumpCost;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float VaultCost;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float ClimbCost;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	float DodgeCost;

	UPROPERTY()
	float BaseTurnRate;
	UPROPERTY()
	float BaseLookUpRate;

/////////////////////////////////////////////// Movement Speed ///////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MovementSpeedModifier;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float BaseMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float RunningMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float CrouchedMovementSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float TargetingMovementSpeed;
};
