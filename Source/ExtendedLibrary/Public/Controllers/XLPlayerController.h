#pragma once

#include "GameFramework/PlayerController.h"
#include "Enums/XLInputMode.h"
#include "Managers/XLPlayerCameraManager.h"
#include "XLPlayerController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);

UCLASS()
class EXTENDEDLIBRARY_API AXLPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY()
	class UXLCharacterInputComponent* CharacterInputComponent;

	UPROPERTY()
	class UXLAirVehicleInputComponent* AirVehicleInputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TEnumAsByte<EInputMode::Type> InputMode;

	UPROPERTY()
	class AXLCharacter* MyCharacter;

	UPROPERTY()
	bool IsFirstPerson;

	UPROPERTY(BlueprintAssignable, Category = "Test")
	FTestDelegate OnTestDelegate;
	
public:

	AXLPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void UnFreeze() override;

	void Reset() override;

	virtual void SetPlayer(UPlayer* Player);
	virtual void SetControllerInputMode(TEnumAsByte<EInputMode::Type> Mode);
	virtual void ResetInputMode();

	UFUNCTION(BlueprintCallable, Category = "Camera")
	void TogglePerspective();

};
