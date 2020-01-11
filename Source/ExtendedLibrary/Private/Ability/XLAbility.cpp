// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAbility.h"

AXLAbility::AXLAbility()
{
}

void AXLAbility::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AXLAbility::Activate()
{
	//Do nothing
}
void AXLAbility::Deactivate()
{
	//Do nothing
}

void AXLAbility::SetMyPawn(AXLCharacter* Character)
{
	MyPawn = Character;
}

void AXLAbility::ConsumeMana(float DeltaSeconds, float Cost)
{
	MyPawn->CharacterResources->CurrentEnergy = MyPawn->CharacterResources->CurrentEnergy - (Cost * DeltaSeconds);
}

void AXLAbility::PlayUtilityAnimation()
{
	if (UtilityAnim)
	{
		MyPawn->PlayAnimMontage(UtilityAnim);
	}
}

void AXLAbility::StartAbility()
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

void AXLAbility::StopAbility()
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

void AXLAbility::ActivateAbility()
{
	Activate();
	Deactivate();
}

void AXLAbility::StartChannelAbility()
{
	Activate();
}

void AXLAbility::StopChannelAbility()
{
	Deactivate();
}

void AXLAbility::ToggleAbility()
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

