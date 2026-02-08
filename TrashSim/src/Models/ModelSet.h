#pragma once

#include <Models/Vehicle/StaticVehicleModel.h>
#include <Models/Atmosphere/USSA1976.h>

struct ModelSet
{
	const StaticVehicleModel* vmod = nullptr;
	const USSA1976* amod = nullptr;
};