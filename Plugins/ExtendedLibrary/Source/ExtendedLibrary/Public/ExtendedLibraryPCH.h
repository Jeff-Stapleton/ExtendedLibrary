#include "Engine.h"
#include "ModuleManager.h"
#include "Internationalization.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"

#include "SlateBasics.h"
#include "SlateExtras.h"
#include "Particles/ParticleSystemComponent.h"
#include "UnrealNetwork.h"
#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

#include "XLCharacter.h"
#include "XLPlayerAnimationManager.h"
#include "XLCharacterStats.h"
#include "XLPlayerState.h"
#include "XLGameState.h"
#include "XLGameMode.h"
#include "XLGameSession.h"
#include "XLOnlineGameSettings.h"


#define COLLISION_WEAPON			ECC_GameTraceChannel1
#define COLLISION_PROJECTILE		ECC_GameTraceChannel2
#define COLLISION_PICKUP			ECC_GameTraceChannel3

#define XL_SURFACE_Default		SurfaceType_Default
#define XL_SURFACE_Concrete		SurfaceType1
#define XL_SURFACE_Dirt			SurfaceType2
#define XL_SURFACE_Water		SurfaceType3
#define XL_SURFACE_Metal		SurfaceType4
#define XL_SURFACE_Wood			SurfaceType5
#define XL_SURFACE_Grass		SurfaceType6
#define XL_SURFACE_Glass		SurfaceType7
#define XL_SURFACE_Flesh		SurfaceType8
#define XL_SURFACE_Energy		SurfaceType9