// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Effects/XLEffect.h"

// Sets default values
AXLEffect::AXLEffect()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXLEffect::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXLEffect::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

