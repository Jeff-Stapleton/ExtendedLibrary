#pragma once

#include "XLFireComponent.generated.h"

UCLASS()
class EXTENDEDLIBRARY_API UXLFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:

	UXLFireComponent();
	void InitializeComponent() override;

	class AXLRangedWeapon* GetWeapon();
};

//class IXLFireComponent
//{
//	GENERATED_BODY()
//
//
//	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Firing")
//	//void StartAttack();
//
//	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Firing")
//	//void StopAttack();
//};