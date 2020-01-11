#pragma once

#include "Components/ActorComponent.h"
#include "XLWeaponGroupFireMode.h"
#include "XLVehicleRangedWeapon.h"
#include "XLVehicleWeaponManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLVehicleWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLVehicleWeaponManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Config)
	TEnumAsByte<EWeaponGroupFireMode::Type> FiringMode;

	//UPROPERTY(EditDefaultsOnly, Category = Inventory)
	//TTuple<TSubclassOf<class AXLVehicleRangedWeapon>, FName> DefaultInventory;
	TArray<class AXLVehicleRangedWeapon*> Inventory;
};