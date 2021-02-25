// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Structs/XLEffectKeyPair.h"

FEffectKeyPair::FEffectKeyPair()
{

}

FEffectKeyPair::FEffectKeyPair(FName id, FActiveGameplayEffectHandle handle)
{
	Id = id;
	EffectHandle = handle;
}