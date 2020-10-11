#pragma once

#include "GameFramework/CharacterMovementComponent.h"
#include "XLMovementComponent.generated.h"

class AXLCharacter;

UCLASS(hidecategories=("CharacterMovement:Walking"))
class EXTENDEDLIBRARY_API UXLMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UXLMovementComponent();

	void UpdateMovementSpeed();

	void ModifyJumpHeight(float HeightModifier);
	void ModifyMovementSpeed(float SpeedModifier);

public:

	AXLCharacter* Character;

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

	UPROPERTY(EditDefaultsOnly, Category = Looking)
	float BaseTurnRate = 45.0f;
	UPROPERTY(EditDefaultsOnly, Category = Looking)
	float BaseLookRate = 45.0f;

/////////////////////////////////////////////// Movement Speed ///////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float MovementSpeedModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float BaseMovementSpeed = 300.0f;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float RunningMovemenModifier = 1.5;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float CrouchedMovementModifier = 0.5;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float PronedMovementModifier = 0.25;

	UPROPERTY(EditDefaultsOnly, Category = Movement)
	float TargetingMovementModifier = 0.75;

	/////////////////////////////////////////////// Movement Speed ///////////////////////////////////////////////

	UPROPERTY(EditDefaultsOnly, Category = Jumping)
	float JumpVelocityModifier = 1.0f;

	UPROPERTY(EditDefaultsOnly, Category = Jumping)
	float JumpVelocity = 420.0f;

};
