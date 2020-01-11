// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/Pawn.h"

#include "Components/Vehicle/Air/XLAirVehicleMovementComponent.h"

#include "Enums/XLInputMode.h"

#include "Interfaces/XLInteractionInterface.h"

#include "XLAirVehicle.generated.h"

UCLASS(config=Game)
class AXLAirVehicle : public ACharacter, public IXLInteractionInterface
{
	GENERATED_BODY()

public:

	/** Spring arm that will offset the camera */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Camera)
	class UCameraComponent* Camera;

	/** Contains and manages the ships weapons */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapons)
	class UXLVehicleWeaponManager* Weapons;

	/** Contains and manages the ships abilities */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	class UXLAbilityManager* Abilities;

	UXLAirVehicleMovementComponent* MovementComponent;
	UCapsuleComponent* MeshCenterOfMass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Abilities)
	bool IsLanded = true;

public:

	AXLAirVehicle(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;

	void TakeOff();

	void Accelerate(float Value);

	void Pitch(float Value);
	void Yaw(float Value);
	void Roll(float Value);

	void Strafe(float Value);
	
	void Move(float DeltaSeconds);
	void RotateController(float DeltaSeconds);
	void RotateMesh(float DeltaSeconds);
	void Stabilize();

	void OnInspect_Implementation(AActor* MyInstigator);

	void OnInteract_Implementation(AActor* MyInstigator);

	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }
};
