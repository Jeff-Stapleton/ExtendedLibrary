// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Characters/XLCharacter.h"
#include "Data/XLCharacterAttributeSet.h"
#include "Components/Character/XLMovementComponent.h"

UXLMovementComponent::UXLMovementComponent()
{
	Character = Cast<AXLCharacter>(GetOwner());

	bWantsInitializeComponent = true;

	CrouchedHalfHeight = 60.0f;
}

void UXLMovementComponent::UpdateMovementSpeed()
{
	if (Character->ActionState == EActionState::Sprinting)
	{
		MaxWalkSpeed = BaseMovementSpeed * RunningMovemenModifier * MovementSpeedModifier;
	}
	else if (Character->PostureState == EPostureState::Crouching)
	{
		MaxWalkSpeed = BaseMovementSpeed * CrouchedMovementModifier * MovementSpeedModifier;
	}
	else if (Character->PostureState == EPostureState::Prone)
	{
		MaxWalkSpeed = BaseMovementSpeed * PronedMovementModifier * MovementSpeedModifier;
	}
	else
	{
		MaxWalkSpeed = BaseMovementSpeed * MovementSpeedModifier;
	}
}

void UXLMovementComponent::ModifyJumpHeight(float HeightModifier)
{
	JumpVelocityModifier = HeightModifier;
	JumpZVelocity = JumpVelocity * JumpVelocityModifier;
}

void UXLMovementComponent::ModifyMovementSpeed(float SpeedModifier)
{
	MovementSpeedModifier = SpeedModifier;
	MaxWalkSpeed = BaseMovementSpeed * MovementSpeedModifier;
}