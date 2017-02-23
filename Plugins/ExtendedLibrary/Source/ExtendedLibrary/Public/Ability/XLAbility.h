// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "XLCharacterResources.h"
#include "XLAbilityType.h"
#include "XLAbility.generated.h"

UCLASS(config = Engine, hidecategories = (UObject, Length), Blueprintable, BlueprintType)
class UXLAbility : public UActorComponent
{
	GENERATED_BODY()

public:

	UXLAbility();

	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void Activate();

	virtual void Deactivate();

	UFUNCTION()
	void SetMyPawn(class AXLCharacter* Owner);

	UFUNCTION(BlueprintCallable, Category = Defaults)
	void ConsumeMana(float Cost, float DeltaSeconds = 1);

	UFUNCTION()
	void PlayUtilityAnimation();

	UFUNCTION()
	void StartAbility();

	UFUNCTION()
	void StopAbility();

	void ActivateAbility();
	void StartChannelAbility();
	void StopChannelAbility();
	void ToggleAbility();

protected:

	UPROPERTY(BlueprintReadOnly, Category = Defaults)
	class AXLCharacter* MyPawn;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	TEnumAsByte<EAbilityType::Type> AbilityType;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FName UtilityName;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	FString UtilityDescription;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	TArray<TSubclassOf<class UXLAbilityEffect>> AbilityEffects;

	UPROPERTY(EditDefaultsOnly, Category = Implementation)
	bool IsActivated;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* UtilityAnim;

	UPROPERTY(EditDefaultsOnly, Category = Implementation)
	TArray<class AXLCharacter*> Targets;
};
