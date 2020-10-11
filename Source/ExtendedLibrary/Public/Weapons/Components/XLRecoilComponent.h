#pragma once

#include "Components/ActorComponent.h"
#include "Structs/XLRecoilData.h"
#include "XLRecoilComponent.generated.h"

class AXLRangedWeapon;
class AXLCharacter;

UCLASS(Blueprintable)
class EXTENDEDLIBRARY_API UXLRecoilComponent : public UActorComponent
{
	GENERATED_BODY()

protected:

	/** The amount the cursor moves when firing. Negative is left or up and positive is right or down */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	TArray<FRecoilData> RecoilPattern;

	/** The amount the weapon pulls vertically when attacking, Negative for up, positive for down */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float VerticalRecoil;

	/** The amount the weapon pulls horizontally when attacking, Negative for left, positive for right */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float HorizontalRecoil;

	/** The speed at which the recoil interpolates from point A to point B */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float RecoilSpeed = 50.0f;

	/** Modifies the recoil by this factor when aiming down the sights */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float RecoilModifier = 1.0f;

	/** The speed at which the settling interpolates from point A to point B */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Ranged)
	float SettlingSpeed = 10.0f;

	AXLRangedWeapon* Owner;
	AXLCharacter* Character;

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
