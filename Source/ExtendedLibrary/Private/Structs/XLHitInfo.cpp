// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "ExtendedLibraryPCH.h"
#include "Structs/XLHitInfo.h"

FXLHitInfo::FXLHitInfo()
	: ActualDamage(0)
	, DamageTypeClass(NULL)
	, PawnInstigator(NULL)
	, DamageCauser(NULL)
	, DamageEventClassID(0)
	, bKilled(false)
	, EnsureReplicationByte(0)
{}

FDamageEvent& FXLHitInfo::GetDamageEvent()
{
	switch (DamageEventClassID)
	{
	case FPointDamageEvent::ClassID:
		if (PointDamageEvent.DamageTypeClass == NULL)
		{
			PointDamageEvent.DamageTypeClass = DamageTypeClass ? DamageTypeClass : UDamageType::StaticClass();
		}
		return PointDamageEvent;

	case FRadialDamageEvent::ClassID:
		if (RadialDamageEvent.DamageTypeClass == NULL)
		{
			RadialDamageEvent.DamageTypeClass = DamageTypeClass ? DamageTypeClass : UDamageType::StaticClass();
		}
		return RadialDamageEvent;

	default:
		if (GeneralDamageEvent.DamageTypeClass == NULL)
		{
			GeneralDamageEvent.DamageTypeClass = DamageTypeClass ? DamageTypeClass : UDamageType::StaticClass();
		}
		return GeneralDamageEvent;
	}
}

void FXLHitInfo::SetDamageEvent(const FDamageEvent& DamageEvent)
{
	DamageEventClassID = DamageEvent.GetTypeID();
	switch (DamageEventClassID)
	{
	case FPointDamageEvent::ClassID:
		PointDamageEvent = *((FPointDamageEvent const*)(&DamageEvent));
		break;
	case FRadialDamageEvent::ClassID:
		RadialDamageEvent = *((FRadialDamageEvent const*)(&DamageEvent));
		break;
	default:
		GeneralDamageEvent = DamageEvent;
	}

	DamageTypeClass = DamageEvent.DamageTypeClass;
}

void FXLHitInfo::EnsureReplication()
{
	EnsureReplicationByte++;
}
