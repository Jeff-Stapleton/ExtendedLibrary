// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAbility.h"

UXLAbility::UXLAbility()
{
	bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLAbility::InitializeComponent()
{
	Super::InitializeComponent();

}

void UXLAbility::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UXLAbility::Activate()
{
	//Do nothing
}
void UXLAbility::Deactivate()
{
	//Do nothing
}

void UXLAbility::SetMyPawn(AXLCharacter* Owner)
{
	MyPawn = Owner;
}

void UXLAbility::ConsumeMana(float DeltaSeconds, float Cost)
{
	MyPawn->CharacterResources->CurrentEnergy = MyPawn->CharacterResources->CurrentEnergy - (Cost * DeltaSeconds);
}

void UXLAbility::PlayUtilityAnimation()
{
	if (UtilityAnim)
	{
		MyPawn->PlayAnimMontage(UtilityAnim);
	}
}

void UXLAbility::StartAbility()
{
	switch (AbilityType)
	{
		case EAbilityType::Activate :
			ActivateAbility();
			break;
		case EAbilityType::Channel :
			StartChannelAbility();
			break;
		case EAbilityType::Toggle :
			ToggleAbility();
			break;
	}
}

void UXLAbility::StopAbility()
{
	switch (AbilityType)
	{
		case EAbilityType::Activate :
			break;
		case EAbilityType::Channel :
			StopChannelAbility();
			break;
		case EAbilityType::Toggle :
			break;
	}
}

void UXLAbility::ActivateAbility()
{
	Activate();
	Deactivate();
}

void UXLAbility::StartChannelAbility()
{
	Activate();
}

void UXLAbility::StopChannelAbility()
{
	Deactivate();
}

void UXLAbility::ToggleAbility()
{
	if (IsActivated)
	{
		IsActivated = false;
		Deactivate();
	}
	else
	{
		IsActivated = true;
		Activate();
	}
}

