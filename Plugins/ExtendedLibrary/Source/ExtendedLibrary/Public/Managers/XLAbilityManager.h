#pragma once

#include "Components/ActorComponent.h"
#include "XLAbilityManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLAbilityManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLAbilityManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};