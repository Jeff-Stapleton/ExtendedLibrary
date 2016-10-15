#pragma once

#include "Components/ActorComponent.h"
#include "XLPlayerEffectManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLPlayerEffectManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLPlayerEffectManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};