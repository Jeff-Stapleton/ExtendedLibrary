// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Characters/XLCharacter.h"
#include "Managers/XLPlayerCameraManager.h"
#include "Components/Character/XLMovementComponent.h"
#include "GameplayEffectExtension.h"
#include "Data/XLCharacterAttributeSet.h"

UXLCharacterAttributeSet::UXLCharacterAttributeSet()
	: Health(1.f)
	, MaxHealth(1.f)
	, MovementSpeed(1.f)
	, JumpVelocity(1.0f)
	, VolumeMultiplier(1.0)
	, Damage(1.f)
	, FOVMultiplier(1.f)
{}

void UXLCharacterAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	// This is called whenever attributes change, so for max health/mana we want to scale the current totals to match
	Super::PreAttributeChange(Attribute, NewValue);

	Character = Cast<AXLCharacter>(GetOwningActor());
	Controller = Cast<AXLPlayerController>(Character->GetController());
	if (Attribute == GetMovementSpeedAttribute())
	{
		if (Character)
		{
			Character->MovementComponent->MaxWalkSpeed = NewValue;
		}
	}
	else if (Attribute == GetJumpVelocityAttribute())
	{
		if (Character)
		{
			Character->MovementComponent->JumpZVelocity = NewValue;
		}
	}
	else if (Attribute == GetFOVMultiplierAttribute())
	{
		if (Controller) CameraManager = Cast<AXLPlayerCameraManager>(Controller->PlayerCameraManager);
		if (Character && Controller && CameraManager)
		{
			CameraManager->TargetFOV = CameraManager->NormalFOV * NewValue;
		}
	}
}

void UXLCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FGameplayEffectContextHandle Context = Data.EffectSpec.GetContext();
	UAbilitySystemComponent* Source = Context.GetOriginalInstigatorAbilitySystemComponent();
	const FGameplayTagContainer& SourceTags = *Data.EffectSpec.CapturedSourceTags.GetAggregatedTags();

	// Compute the delta between old and new, if it is available
	float DeltaValue = 0;
	if (Data.EvaluatedData.ModifierOp == EGameplayModOp::Type::Additive)
	{
		// If this was additive, store the raw delta value to be passed along later
		DeltaValue = Data.EvaluatedData.Magnitude;
	}

	// Get the Target actor, which should be our owner
	AActor* TargetActor = nullptr;
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		TargetActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Character = Cast<AXLCharacter>(TargetActor);
		Controller = Cast<AXLPlayerController>(Character->GetController());
	}

	if (Data.EvaluatedData.Attribute == GetMovementSpeedAttribute())
	{
		if (Character)
		{
			Character->MovementComponent->MaxWalkSpeed = GetMovementSpeed();
		}
	}
	else if (Data.EvaluatedData.Attribute == GetJumpVelocityAttribute())
	{
		if (Character)
		{
			Character->MovementComponent->JumpZVelocity = GetJumpVelocity();
		}
	}
	else if (Data.EvaluatedData.Attribute == GetFOVMultiplierAttribute())
	{
		if (Controller) CameraManager = Cast<AXLPlayerCameraManager>(Controller->PlayerCameraManager);
		if (Character && Controller && CameraManager)
		{
			CameraManager->TargetFOV = GetFOVMultiplier();
		}
	}
}


void UXLCharacterAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UXLCharacterAttributeSet, MaxHealth);
	DOREPLIFETIME(UXLCharacterAttributeSet, Health);
	DOREPLIFETIME(UXLCharacterAttributeSet, MovementSpeed);
	DOREPLIFETIME(UXLCharacterAttributeSet, JumpVelocity);
	DOREPLIFETIME(UXLCharacterAttributeSet, VolumeMultiplier);
	DOREPLIFETIME(UXLCharacterAttributeSet, Damage);
	DOREPLIFETIME(UXLCharacterAttributeSet, FOVMultiplier);
}

void UXLCharacterAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLCharacterAttributeSet, MaxHealth, OldMaxHealth);
}

void UXLCharacterAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLCharacterAttributeSet, Health, OldHealth);
}

void UXLCharacterAttributeSet::OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLCharacterAttributeSet, MovementSpeed, OldMovementSpeed);
}

void UXLCharacterAttributeSet::OnRep_JumpVelocity(const FGameplayAttributeData& OldJumpVelocity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLCharacterAttributeSet, JumpVelocity, OldJumpVelocity);
}

void UXLCharacterAttributeSet::OnRep_VolumeMultiplier(const FGameplayAttributeData& OldVolumeMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLCharacterAttributeSet, VolumeMultiplier, OldVolumeMultiplier);
}

void UXLCharacterAttributeSet::OnRep_Damage(const FGameplayAttributeData& OldDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLCharacterAttributeSet, Damage, OldDamage);
}

void UXLCharacterAttributeSet::OnRep_FOVMultiplier(const FGameplayAttributeData& OldFOVMultiplier)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UXLCharacterAttributeSet, FOVMultiplier, OldFOVMultiplier);
}
