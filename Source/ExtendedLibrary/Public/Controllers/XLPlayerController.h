#pragma once

#include "GameFramework/PlayerController.h"
#include "Enums/XLInputMode.h"
#include "XLPlayerController.generated.h"

class UXLCharacterInputComponent;
class AXLCharacter;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTestDelegate);

UCLASS()
class EXTENDEDLIBRARY_API AXLPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UPROPERTY()
	UXLCharacterInputComponent* CharacterInputComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	TEnumAsByte<EInputMode::Type> InputMode;

	UPROPERTY()
	AXLCharacter* MyCharacter;

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
