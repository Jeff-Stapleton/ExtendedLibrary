// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLHoverEffect.h"

AXLHoverEffect::AXLHoverEffect()
{
}

void AXLHoverEffect::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	/*GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("Is Falling: %d"), Character->MovementComponent->IsFalling()));
	if (Character && !Character->MovementComponent->IsFalling())
	{
		Deactivate();
	}*/
}

void AXLHoverEffect::Activate(AXLCharacter* Instigator, AXLCharacter* Target, FXLEffectOptions* Options)
{
	if (Instigator && Target)
	{
		Character = Instigator;
		Character->MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);
		if (Duration > 0)
		{
			GetWorldTimerManager().SetTimer(TimerHandle_Duration, this, &AXLHoverEffect::Deactivate, Duration, false);
		}
	}
}

void AXLHoverEffect::Deactivate()
{
	if (Character)
	{
		Character->MovementComponent->SetMovementMode(EMovementMode::MOVE_Walking);
		Destroy();
	}
}