#pragma once

#include "Components/ActorComponent.h"
#include "XLPlayerAnimationManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLPlayerAnimationManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLPlayerAnimationManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* DeathAnim;

};