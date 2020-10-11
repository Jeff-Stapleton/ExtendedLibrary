// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Structs/XLWeaponSounds.h"

//UXLWeaponSoundManager::UXLWeaponSoundManager()
//{
//    bWantsInitializeComponent = true;
//}
//
//void UXLWeaponSoundManager::InitializeComponent()
//{
//    Super::InitializeComponent();
//
//    Owner = Cast<AXLRangedWeapon>(GetOwner());
//    Owner->WeaponStateDelegate.AddDynamic(this, &UXLWeaponSoundManager::DetermineAction);
//}
//
//void UXLWeaponSoundManager::DetermineAction()
//{
//    if (Owner->WeaponState == EWeaponState::Firing)
//    {
//        ActivateFireAC();
//    }
//    else
//    {
//        DeactivateFireAC();
//    }
//}
//
//void UXLWeaponSoundManager::ActivateFireAC()
//{
//    if (FireAC == NULL)
//    {
//        //FireAC = PlaySound(FireLoopSound);
//    }
//}
//
//void UXLWeaponSoundManager::DeactivateFireAC()
//{
//    if (FireAC)
//    {
//    	FireAC->FadeOut(0.1f, 0.0f);
//    	FireAC = NULL;
//
//    	//PlaySound(FireFinishSound);
//    }
//}
//
//UAudioComponent* UXLWeaponSoundManager::PlaySound(USoundCue* Sound)
//{
//    UAudioComponent* AC = NULL;
//    if (Sound && Owner->Character)
//    {
//        AC = UGameplayStatics::SpawnSoundAttached(Sound, Owner->Character->GetRootComponent());
//    }
//    return AC;
//}


