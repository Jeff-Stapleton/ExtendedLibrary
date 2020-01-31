#pragma once

#include "XLRangedWeapon.h"
#include "XLCharacter.h"
#include "XLPlayerController.h"
#include "XLAIController.h"
#include "XLADSComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLADSComponent : public UActorComponent
{
	GENERATED_BODY()

	UXLADSComponent();

	void InitializeComponent() override;

public:
	class AXLRangedWeapon* Owner;
	class AXLCharacter* Character;
	class AXLPlayerController* Controller;
	class AXLPlayerCameraManager* CameraManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float DefaultFOV = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float FOV = 45;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Base)
	float Speed = 10.0f;

private:
	UFUNCTION()
	void DetermineAction();

};