// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Structs/XLWeaponAnimations.h"
//
//UXLWeaponAnimationManager::UXLWeaponAnimationManager()
//{
//	bWantsInitializeComponent = true;
//}
//
//void UXLWeaponAnimationManager::InitializeComponent()
//{
//	Super::InitializeComponent();
//
//	Owner = Cast<AXLRangedWeapon>(GetOwner());
//
//	Owner->WeaponStateDelegate.AddDynamic(this, &UXLWeaponAnimationManager::DetermineAction);
//}
//
//void UXLWeaponAnimationManager::DetermineAction()
//{
//	if (Owner->WeaponState == EWeaponState::Reloading)
//	{
//		StartReload();
//	}
//	else
//	{
//		StopAnimation();
//		Owner->GetWorldTimerManager().ClearTimer(ReloadTimer);
//	}
//}
//
//void UXLWeaponAnimationManager::StartReload()
//{
//	float Duration = PlayAnimation(ReloadAnim);
//
//	Owner->GetWorldTimerManager().SetTimer(ReloadTimer, this, &UXLWeaponAnimationManager::FinishReload, FMath::Max(0.1f, Duration), false);
//}
//
//void UXLWeaponAnimationManager::FinishReload()
//{
//	Owner->ReloadEventDelegate.Broadcast();;
//
//	Owner->WeaponState = EWeaponState::Idle;
//	Owner->WeaponStateDelegate.Broadcast();
//}
//
//float UXLWeaponAnimationManager::PlayAnimation(UAnimMontage* Animation, float Duration)
//{
//	if (Owner->Character && Animation)
//	{
//		float length = Animation->CalculateSequenceLength();
//		float rate = length / Duration;
//
//		Duration = Owner->Character->PlayAnimMontage(Animation, rate);
//	}
//	return Duration;
//}
//
//void UXLWeaponAnimationManager::StopAnimation()
//{
//	if (Owner->Character)
//	{
//		Owner->Character->StopAnimMontage(nullptr);
//	}
//}
