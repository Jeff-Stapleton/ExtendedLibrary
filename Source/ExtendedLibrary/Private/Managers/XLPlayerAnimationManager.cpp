// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPlayerAnimationManager.h"

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



