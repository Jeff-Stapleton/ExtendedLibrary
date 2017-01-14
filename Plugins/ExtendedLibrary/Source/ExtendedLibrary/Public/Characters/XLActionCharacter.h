#pragma once

#include "XLActionCharacter.generated.h"

UCLASS()
class AXLActionCharacter : public AXLCharacter
{
	GENERATED_BODY()

public: 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;

	UPROPERTY()
	class UCameraComponent* PerspectiveCamera;

	AXLActionCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;

};
