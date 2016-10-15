#pragma once

#include "Components/ActorComponent.h"
#include "XLPlayerSoundManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLPlayerSoundManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLPlayerSoundManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

};