#pragma once

#include "XLInteractionInterface.generated.h"

UINTERFACE(BlueprintType)
class UXLInteractionInterface : public UInterface
{
	GENERATED_BODY()
};

class IXLInteractionInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void OnInspect(AActor* Instigator);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interact")
	void OnInteract(AActor* Instigator);

};