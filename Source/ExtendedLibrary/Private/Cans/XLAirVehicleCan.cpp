// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLAirVehicleCan.h"

bool XLAirVehicleCan::Accelerate(AXLAirVehicle* Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLAirVehicleCan::Pitch(AXLAirVehicle* Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLAirVehicleCan::Yaw(AXLAirVehicle* Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLAirVehicleCan::Roll(AXLAirVehicle* Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLAirVehicleCan::Strafe(AXLAirVehicle* Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLAirVehicleCan::Move(AXLAirVehicle* Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLAirVehicleCan::Rotate(AXLAirVehicle* Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLAirVehicleCan::Stabilize(AXLAirVehicle* Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool XLAirVehicleCan::Die(AXLAirVehicle * Vehicle)
{
	if (Vehicle && Vehicle->Controller)
	{
		return true;
	}
	else
	{
		return false;
	}
}
