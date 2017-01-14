// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAbilityManager.h"

UXLAbilityManager::UXLAbilityManager()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLAbilityManager::InitializeComponent()
{
	Super::InitializeComponent();

	MyPawn = Cast<AXLCharacter>(GetOwner());

	InitializeAbilities();
}

void UXLAbilityManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UXLAbilityManager::InitializeAbilities()
{
	for (int32 i = 0; i < AbilitiesBP.Num(); i++)
	{
		if (AbilitiesBP[i])
		{
			class UXLAbility* NewAbility = AbilitiesBP[i].GetDefaultObject();
			NewAbility->SetMyPawn(MyPawn);
			Abilities.AddUnique(NewAbility);
		}
	}
}


void UXLAbilityManager::ActivateAbility(int32 Ability)
{
	Abilities[Ability]->Activate();
}
void UXLAbilityManager::DeactivateAbility(int32 Ability)
{
	Abilities[Ability]->Deactivate();
}



