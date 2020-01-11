#pragma once

#include "Components/ActorComponent.h"
#include "XLWeaponManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLWeaponManager : public UActorComponent
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AXLWeapon> > DefaultInventory;

	UPROPERTY(Replicated, EditAnywhere, BlueprintReadWrite, Category = Weapons)
	TArray<class AXLWeapon*> Inventory;

	UXLWeaponManager();

	void DestroyInventory();

	UFUNCTION(BlueprintCallable, Category = Weapon)
	AXLWeapon* GetWeapon(int32 Weapon);

	int32 GetNextWeaponIndex(int32 Weapon);

	int32 GetPreviousWeaponIndex(int32 Weapon);
};