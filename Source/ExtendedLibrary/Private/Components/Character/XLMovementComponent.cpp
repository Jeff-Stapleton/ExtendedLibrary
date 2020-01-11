// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLMovementComponent.h"

UXLMovementComponent::UXLMovementComponent()
{
	Character = Cast<AXLCharacter>(GetOwner());

	JumpZVelocity = JumpVelocity * JumpVelocityModifier;
	MaxWalkSpeed = BaseMovementSpeed * MovementSpeedModifier;
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

void UXLMovementComponent::ModifyJumpHeight(float NewModifier)
{
	JumpVelocityModifier = NewModifier;
	JumpZVelocity = JumpVelocity * JumpVelocityModifier;
}