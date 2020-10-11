// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Managers/XLPlayerAnimationManager.h"

UXLPlayerAnimationManager::UXLPlayerAnimationManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLPlayerAnimationManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLPlayerAnimationManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UXLPlayerAnimationManager::SetAnimClass(TSubclassOf<UAnimInstance> NewAnimClass)
{
	AXLCharacter* Character = Cast<AXLCharacter>(GetOwner());

	Character->Head->SetAnimInstanceClass(NewAnimClass);
	Character->UpperBody->SetAnimInstanceClass(NewAnimClass);
	Character->LowerBody->SetAnimInstanceClass(NewAnimClass);
	Character->Hands->SetAnimInstanceClass(NewAnimClass);
	Character->Feet->SetAnimInstanceClass(NewAnimClass);
}


