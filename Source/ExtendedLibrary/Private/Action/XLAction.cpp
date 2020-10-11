// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Action/XLAction.h"

// Sets default values
AXLAction::AXLAction()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AXLAction::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AXLAction::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

