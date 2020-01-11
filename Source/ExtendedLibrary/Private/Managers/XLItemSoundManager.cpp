// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLItemSoundManager.h"

UXLItemSoundManager::UXLItemSoundManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UXLItemSoundManager::BeginPlay()
{
	Super::BeginPlay();
}

void UXLItemSoundManager::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

