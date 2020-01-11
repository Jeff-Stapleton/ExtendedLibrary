#pragma once

#include "Components/ActorComponent.h"
#include "XLRecoilData.h"
#include "XLRecoilComponent.generated.h"

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLRecoilComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	class AXLRangedWeapon* Owner;
	class AXLCharacter* Character;

	int32 RecoilIndex;

	TArray<FRecoilData> PendingRecoil;
	FRecoilData PendingSettling;

	FRecoilData CurrentSettling;
	FRecoilData CurrentRecoil;

public:
	UXLRecoilComponent();

    void InitializeComponent() override;

	virtual void OnRegister() override;

	void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(Reliable, Client)
    void DetermineAction();
	UFUNCTION(Reliable, Client)
	void StopAttacking();
	UFUNCTION(Reliable, Client)
	void ResetSettling();

protected:

	void QueueRecoil();
	void QueueSettling();
	void IncrementRecoilIndex();

	UFUNCTION(Reliable, Client)
	void ApplyRecoil(float DeltaSeconds);
	UFUNCTION(Reliable, Client)
	void ApplySettling(float DeltaSeconds);
};