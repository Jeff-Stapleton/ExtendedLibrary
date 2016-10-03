#pragma once

#include "Components/ActorComponent.h"
#include "XLAnimationManager.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UXLAnimationManager : public UActorComponent
{
	GENERATED_BODY()

public:
	UXLAnimationManager();

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = Animation)
	UAnimMontage* DeathAnim;

};