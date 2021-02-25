#pragma once

#include "Characters/XLCharacter.h"

#include "XLPlayerCharacter.generated.h"

class USpringArmComponent;
class UXLCamera;

UCLASS()
class EXTENDEDLIBRARY_API AXLPlayerCharacter : public AXLCharacter
{
	GENERATED_BODY()

public: 

	UPROPERTY()
	bool IsFirstPerson = false;

	AXLPlayerCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UXLCamera* Camera;

	UFUNCTION()
	void ToggleCamera();
};
