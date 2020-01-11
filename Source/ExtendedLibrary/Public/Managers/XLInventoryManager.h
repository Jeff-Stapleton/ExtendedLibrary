#pragma once

#include "Components/ActorComponent.h"
#include "XLInventoryManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLInventoryManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	TArray<TSubclassOf<class AXLItem> > DefaultInventory;

	UPROPERTY(Replicated, BlueprintReadWrite, Category = Inventory)
	TArray<class AXLItem*> Inventory;

	UPROPERTY(EditDefaultsOnly, Category = Inventory)
	int32 InventorySize;

	UXLInventoryManager();

	void DestroyInventory();

	UFUNCTION(BlueprintCallable, Category = Inventory)
	AXLItem* GetItem(int32 item);

	UFUNCTION(BlueprintCallable, Category = Inventory)
	void AddItem(TSubclassOf<class AXLItem> item, AActor* owner);
	UFUNCTION(Reliable, Server, WithValidation)
	void ServerAddItem(TSubclassOf<class AXLItem> item, AActor* owner);

};