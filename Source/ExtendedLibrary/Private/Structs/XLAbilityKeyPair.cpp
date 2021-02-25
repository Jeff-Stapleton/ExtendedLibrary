// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Structs/XLAbilityKeyPair.h"

FAbilityKeyPair::FAbilityKeyPair()
{

}

FAbilityKeyPair::FAbilityKeyPair(FName id, FGameplayAbilitySpecHandle handle)
{
	Id = id;
	AbilityHandle = handle;
}