#pragma once

#include "Vehicles/Air/XLAirVehicle.h"

class XLAirVehicleCan
{
public:
	static bool Accelerate(AXLAirVehicle* Vehicle);

	static bool Pitch(AXLAirVehicle* Vehicle);
	static bool Yaw(AXLAirVehicle* Vehicle);
	static bool Roll(AXLAirVehicle* Vehicle);

	static bool Strafe(AXLAirVehicle* Vehicle);

	static bool Move(AXLAirVehicle* Vehicle);
	static bool Rotate(AXLAirVehicle* Vehicle);
	static bool Stabilize(AXLAirVehicle* Vehicle);

	static bool Die(AXLAirVehicle* Vehicle);
};
