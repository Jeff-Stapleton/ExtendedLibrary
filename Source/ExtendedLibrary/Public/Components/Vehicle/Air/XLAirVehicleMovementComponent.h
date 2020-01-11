#pragma once

#include "XLAirVehicleMovementComponent.generated.h"

UCLASS(hidecategories=("CharacterMovement:Walking"))
class UXLAirVehicleMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

	//UXLAirVehicleMovementComponent();

public:

	//void UpdateMovementSpeed();

	//void ModifyJumpHeight(float NewModifier);

public:

	/** Forward speed while full throttled */
	UPROPERTY(Category = "Config|Speed", EditAnywhere)
	float BoostSpeed = 5000.0f;

	/** Standard forward speed while flying*/
	UPROPERTY(Category = "Config|Speed", EditAnywhere)
	float DefaultSpeed = 5000.0f;

	/** Min forward speed */
	UPROPERTY(Category = "Config|Speed", EditAnywhere)
	float MinSpeed = 0.0f;

	float TargetSpeed = 0.0f;
	float CurrentSpeed = 0.0f;

	/** How quickly pawn can rise and dive */
	UPROPERTY(Category = "Config|Acceleration", EditAnywhere)
	float PitchSpeed = 45.0f;
	float ControllerTargetPitch = 0.0f;
	float ControllerCurrentPitch = 0.0f;
	float MeshTargetPitch = 0.0f;
	float MeshCurrentPitch = 0.0f;

	/** How quickly pawn can turn */
	UPROPERTY(Category = "Config|Acceleration", EditAnywhere)
	float YawSpeed = 45.0f;
	float ControllerTargetYaw = 0.0f;
	float ControllerCurrentYaw = 0.0f;
	float MeshTargetYaw = 0.0f;
	float MeshCurrentYaw = 0.0f;

	/** How quickly pawn can roll */
	UPROPERTY(Category = "Config|Acceleration", EditAnywhere)
	float RollSpeed = 45.0f;
	float ControllerTargetRoll = 0.0f;
	float ControllerCurrentRoll = 0.0f;
	float MeshTargetRoll = 0.0f;
	float MeshCurrentRoll = 0.0f;

	/** How quickly pawn starts to rise and dive */
	UPROPERTY(Category = "Config|Responsiveness", EditAnywhere)
	float PitchResponsiveness = 0.2f;

	/** How quickly pawn starts to rise and dive */
	UPROPERTY(Category = "Config|Responsiveness", EditAnywhere)
	float YawResponsiveness = 0.2f;

	/** How quickly pawn starts to rise and dive */
	UPROPERTY(Category = "Config|Responsiveness", EditAnywhere)
	float RollResponsiveness = 0.2f;

	/** The degrees the ship rolls while turning */
	UPROPERTY(Category = "Config|Cosmetic", EditAnywhere)
	float RollWhileTurning = 0.0f;

	/** The degrees the ship rolls while turning */
	UPROPERTY(Category = "Config|Cosmetic", EditAnywhere)
	float RollWhileStrafing = 0.0f;

	/** How quickly pawn starts to rise and dive */
	UPROPERTY(Category = "Config|QOL", EditAnywhere)
	float StabilizeRate = 0.025f;

	bool IsRolling = false;

};
