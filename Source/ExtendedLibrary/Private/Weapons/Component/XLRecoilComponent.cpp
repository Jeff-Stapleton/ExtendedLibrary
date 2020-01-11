// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLRecoilComponent.h"

UXLRecoilComponent::UXLRecoilComponent()
{
	bReplicates = true;
    bWantsInitializeComponent = true;
	PrimaryComponentTick.bCanEverTick = true;
	RecoilIndex = 0;
}

void UXLRecoilComponent::InitializeComponent()
{
    Super::InitializeComponent();

	Owner = Cast<AXLRangedWeapon>(GetOwner());

	Owner->WeaponStateDelegate.AddDynamic(this, &UXLRecoilComponent::StopAttacking);
	Owner->WeaponAimDelegate.AddDynamic(this, &UXLRecoilComponent::ResetSettling);
	Owner->FireEventDelegate.AddDynamic(this, &UXLRecoilComponent::DetermineAction);
}

void UXLRecoilComponent::OnRegister()
{
	Super::OnRegister();
}


void UXLRecoilComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PendingRecoil.Num() > 0)
	{
		ApplyRecoil(DeltaTime);
	}
	if (PendingRecoil.Num() <= 0 && !PendingSettling.IsZero())
	{
		ApplySettling(DeltaTime);
	}
}

void UXLRecoilComponent::DetermineAction_Implementation()
{
	QueueRecoil();
	QueueSettling();
	IncrementRecoilIndex();
}

void UXLRecoilComponent::StopAttacking_Implementation()
{
	if (Owner->WeaponState == EWeaponState::Idle)
	{
		RecoilIndex = 0;
	}
}

void UXLRecoilComponent::ResetSettling_Implementation()
{
	PendingSettling.Reset();
	CurrentSettling.Reset();
}

void UXLRecoilComponent::QueueRecoil()
{
	if (Owner->Character->TargetingState == ETargetingState::ADS)
	{
		FRecoilData ModifiedRecoil = Owner->WeaponStats->RecoilPattern[RecoilIndex];
		ModifiedRecoil.VerticalRecoil *= Owner->WeaponStats->RecoilModifier;
		ModifiedRecoil.HorizontalRecoil *= Owner->WeaponStats->RecoilModifier;

		PendingRecoil.Add(ModifiedRecoil);
	}
	else
	{
		PendingRecoil.Add(Owner->WeaponStats->RecoilPattern[RecoilIndex]);
	}
}

void UXLRecoilComponent::QueueSettling()
{
	if (Owner->Character->TargetingState == ETargetingState::ADS)
	{
		FRecoilData ModifiedRecoil = Owner->WeaponStats->RecoilPattern[RecoilIndex];
		ModifiedRecoil.VerticalRecoil *= Owner->WeaponStats->RecoilModifier * -1;
		ModifiedRecoil.HorizontalRecoil *= Owner->WeaponStats->RecoilModifier * -1;

		PendingSettling.VerticalRecoil += ModifiedRecoil.VerticalRecoil;
		PendingSettling.HorizontalRecoil += ModifiedRecoil.HorizontalRecoil;
	}
	else
	{
		FRecoilData ModifiedRecoil = Owner->WeaponStats->RecoilPattern[RecoilIndex];
		ModifiedRecoil.VerticalRecoil *= -1;
		ModifiedRecoil.HorizontalRecoil *= -1;

		PendingSettling.VerticalRecoil += ModifiedRecoil.VerticalRecoil;
		PendingSettling.HorizontalRecoil += ModifiedRecoil.HorizontalRecoil;
	}
}

void UXLRecoilComponent::IncrementRecoilIndex()
{
	// If for any reason there are more rounds that recoil patterns, loop back to 0
	if (Owner->WeaponStats->RecoilPattern.IsValidIndex(RecoilIndex + 1))
	{
		RecoilIndex++;
	}
	else
	{
		RecoilIndex = 0;
	}
}



void UXLRecoilComponent::ApplyRecoil_Implementation(float DeltaSeconds)
{
	if (PendingRecoil.Num() > 0)
	{
		float VerticalRecoil = CurrentRecoil.VerticalRecoil;
		float HorizontalRecoil = CurrentRecoil.HorizontalRecoil;

		CurrentRecoil.VerticalRecoil = FMath::FInterpTo(CurrentRecoil.VerticalRecoil, PendingRecoil[0].VerticalRecoil, DeltaSeconds, Owner->WeaponStats->RecoilSpeed);
		CurrentRecoil.HorizontalRecoil = FMath::FInterpTo(CurrentRecoil.HorizontalRecoil, PendingRecoil[0].HorizontalRecoil, DeltaSeconds, Owner->WeaponStats->RecoilSpeed);

		Owner->Character->AddControllerPitchInput(CurrentRecoil.VerticalRecoil - VerticalRecoil);
		Owner->Character->AddControllerYawInput(CurrentRecoil.HorizontalRecoil - HorizontalRecoil);

		if (CurrentRecoil == PendingRecoil[0])
		{
			PendingRecoil.RemoveAt(0);
			CurrentRecoil.Reset();
		}
	}
}

void UXLRecoilComponent::ApplySettling_Implementation(float DeltaSeconds)
{
	float VerticalSettling = CurrentSettling.VerticalRecoil;
	float HorizontalSettling = CurrentSettling.HorizontalRecoil;

	CurrentSettling.VerticalRecoil = FMath::FInterpTo(CurrentSettling.VerticalRecoil, PendingSettling.VerticalRecoil, DeltaSeconds, Owner->WeaponStats->SettlingSpeed);
	CurrentSettling.HorizontalRecoil = FMath::FInterpTo(CurrentSettling.HorizontalRecoil, PendingSettling.HorizontalRecoil, DeltaSeconds, Owner->WeaponStats->SettlingSpeed);

	Owner->Character->AddControllerPitchInput(CurrentSettling.VerticalRecoil - VerticalSettling);
	Owner->Character->AddControllerYawInput(CurrentSettling.HorizontalRecoil - HorizontalSettling);

	if (CurrentSettling == PendingSettling)
	{
		ResetSettling();
	}
}

//void UXLRecoilComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
//{
//	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
//
//	DOREPLIFETIME_CONDITION(UXLRecoilComponent, PendingRecoil, COND_OwnerOnly);
//	DOREPLIFETIME_CONDITION(UXLRecoilComponent, PendingSettling, COND_OwnerOnly);
//}
