#pragma once

#include "Components/ActorComponent.h"
#include "XLAbilityManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLAbilityManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLAbilityManager();

	virtual void InitializeComponent() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void ActivateAbility(int32 Ability);
	UFUNCTION()
	void DeactivateAbility(int32 Ability);

protected:
	void InitializeAbilities();

protected:
	class AXLCharacter* MyPawn;

	UPROPERTY(EditAnywhere, Category = Ability)
	TArray<TSubclassOf<class UXLAbility>> AbilitiesBP;

	TArray<class UXLAbility*> Abilities;
};