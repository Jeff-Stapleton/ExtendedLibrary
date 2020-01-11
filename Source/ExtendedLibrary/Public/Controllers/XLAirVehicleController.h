#pragma once

#include "GameFramework/PlayerController.h"
#include "XLAirVehicleController.generated.h"

UCLASS()
class AXLAirVehicleController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AXLAirVehicleController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetPlayer(UPlayer* Player);

protected:

	virtual void UnFreeze() override;

	void Reset() override;

private:

	UPROPERTY()
	AXLAirVehicle* MyVehicle;

};
