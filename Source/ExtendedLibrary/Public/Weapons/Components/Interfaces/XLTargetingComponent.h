#pragma once

#include "Blueprint/UserWidget.h"
#include "XLTargetingComponent.generated.h"

class AXLItem;
class AXLCharacter;
class AXLPlayerController;
class AXLPlayerCameraManager;
class UUserWidget;

UCLASS()
class EXTENDEDLIBRARY_API UXLTargetingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	AXLItem* Owner;
	AXLCharacter* Character;
	AXLPlayerController* Controller;
	AXLPlayerCameraManager* CameraManager;

	UPROPERTY(EditDefaultsOnly, Category = "XL|UI")
	TSubclassOf<UUserWidget> ScopeWidgetBP;

	UUserWidget* ScopeWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|UI")
	float BlindDuration = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Camera")
	float DefaultFOV = 90;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Camera")
	float FOV = 45;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "XL|Camera")
	float Speed = 10.0f;

	class AXLItem* GetWeapon();
};
