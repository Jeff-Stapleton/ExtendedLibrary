#pragma once

#include "Components/ActorComponent.h"
#include "XLEffectManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLEffectManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLEffectManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};