#pragma once

#include "XLCharacter.h"
#include "XLActionCharacter.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API AXLActionCharacter : public AXLCharacter
{
	GENERATED_BODY()

public: 

	UPROPERTY()
	bool IsFirstPerson = false;

	AXLActionCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UXLCamera* Camera;

	UFUNCTION()
	void ToggleCamera();

	void StartAim() override;
	void StopAim() override;

};
