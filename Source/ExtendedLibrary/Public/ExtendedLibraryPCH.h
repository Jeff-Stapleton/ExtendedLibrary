#include "Engine.h"
#include "ModuleManager.h"
#include "Internationalization.h"

#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "Net/UnrealNetwork.h"

#include "XLAirVehicle.h"
#include "XLCharacter.h"
#include "XLPlayerController.h"
#include "XLCharacterStats.h"
#include "XLItem.h"
#include "XLRangedWeapon.h"
#include "XLAimingComponent.h"
#include "XLCharacterResources.h"
#include "XLProjectileComponent.h"
#include "XLAmmoComponent.h"
#include "XLRecoilComponent.h"
#include "XLFireComponent.h"
#include "XLADSComponent.h"

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

#define COLLISION_PHYSICAL_OBJECT	ECC_GameTraceChannel1
#define COLLISION_PHASE_OBJECT		ECC_GameTraceChannel2
#define COLLISION_PROJECTILE		ECC_GameTraceChannel3
#define COLLISION_PICKUP			ECC_GameTraceChannel4

#define UNDEFINED					MAX_int32
