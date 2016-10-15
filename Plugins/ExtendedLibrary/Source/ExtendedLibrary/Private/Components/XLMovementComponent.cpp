// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLMovementComponent.h"

UXLMovementComponent::UXLMovementComponent()
{
	BaseTurnRate = 25.f;
	BaseLookUpRate = 25.f;

	MovementSpeedModifier = 1.0f;
	BaseMovementSpeed = 400.0f;
	RunningMovementSpeed = 650.0f;
	CrouchedMovementSpeed = 300.0f;
	TargetingMovementSpeed = 200.0f;
}
