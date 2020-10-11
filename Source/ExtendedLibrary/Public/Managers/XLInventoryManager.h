#pragma once

#include "Components/ActorComponent.h"
#include "XLInventoryManager.generated.h"

class AXLItem;
class AXLCharacter;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLInventoryManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<AXLItem> > DefaultInventory;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = Inventory)
	TArray<AXLItem*> Inventory;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	int32 InventorySize;

	UXLInventoryManager();

	void DestroyInventory();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	AXLItem* GetItem(int32 index);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void AddItem(TSubclassOf<AXLItem> item, AXLCharacter* owner);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerAddItem(TSubclassOf<AXLItem> item, AXLCharacter* owner);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void RemoveItem(int32 index, AXLCharacter* owner);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerRemoveItem(int32 index, AXLCharacter* owner);

};