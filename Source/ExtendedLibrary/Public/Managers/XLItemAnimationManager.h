#pragma once

#include "Components/ActorComponent.h"
#include "XLItemAnimationManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLItemAnimationManager : public UActorComponent
{
	GENERATED_BODY()

public:

	/** equip animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* LootAnim;

	/** holster animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* EquipAnim;

	/** melee animations */
	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* UnequipAnim;

public:
	UXLItemAnimationManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};