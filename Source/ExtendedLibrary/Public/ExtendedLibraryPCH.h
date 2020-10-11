#include "Engine.h"
#include "Modules/ModuleManager.h"
#include "Internationalization/Internationalization.h"
#include "ParticleDefinitions.h"
#include "SoundDefinitions.h"
#include "Net/UnrealNetwork.h"

#include "Characters/XLCharacter.h"
#include "Controllers/XLPlayerController.h"


#define XL_SURFACE_Default			SurfaceType_Default
#define XL_SURFACE_Concrete			SurfaceType1
#define XL_SURFACE_Dirt				SurfaceType2
#define XL_SURFACE_Water			SurfaceType3
#define XL_SURFACE_Metal			SurfaceType4
#define XL_SURFACE_Wood				SurfaceType5
#define XL_SURFACE_Grass			SurfaceType6
#define XL_SURFACE_Glass			SurfaceType7
#define XL_SURFACE_Flesh			SurfaceType8
#define XL_SURFACE_Energy			SurfaceType9
#define XL_SURFACE_Bark				SurfaceType10
#define XL_SURFACE_Vegetation		SurfaceType11
#define XL_SURFACE_Plastic			SurfaceType12

#define COLLISION_PHYSICAL_OBJECT	ECC_GameTraceChannel1
#define COLLISION_PHASE_OBJECT		ECC_GameTraceChannel2
#define COLLISION_PROJECTILE		ECC_GameTraceChannel3
#define COLLISION_PICKUP			ECC_GameTraceChannel4

#define UNDEFINED					MAX_int32
