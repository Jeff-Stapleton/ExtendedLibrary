#pragma once

#include "GameFramework/PlayerController.h"
#include "XLPlayerController.generated.h"

UCLASS()
class AXLPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	AXLPlayerController();

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetPlayer(UPlayer* Player);

protected:

	virtual void Move(float Direction);
	virtual void Strafe(float Direction);

	virtual void Turn(float Direction);
	virtual void Look(float Direction);

	virtual void Jump();

	virtual void Dodge();

	virtual void StartSprint();
	virtual void StopSprint();

	virtual void StartAttack();
	virtual void StopAttack();

	virtual void Reload();

	virtual void Melee();

	virtual void StartAbility1();
	virtual void StopAbility1();

	virtual void StartAbility2();
	virtual void StopAbility2();

	virtual void StartAbility3();
	virtual void StopAbility3();

	virtual void UnFreeze() override;

	void Reset() override;

private:

	UPROPERTY()
	AXLCharacter* MyCharacter;

};
