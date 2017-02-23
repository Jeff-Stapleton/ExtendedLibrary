#pragma once

#include "Components/ActorComponent.h"
#include "XLWeaponManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLWeaponManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AXLWeapon> > DefaultInventory;
	TArray<class AXLWeapon*> Inventory;

};