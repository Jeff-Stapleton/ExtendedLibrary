// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Projectiles/XLImpactFX.h"


AXLImpactFX::AXLImpactFX(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	SetAutoDestroyWhenFinished(true);
}

void AXLImpactFX::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (GetLocalRole() == ROLE_Authority)
	{
		UPhysicalMaterial* HitPhysMat = SurfaceHit.PhysMaterial.Get();
		EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitPhysMat);

		UParticleSystem* ImpactFX = GetImpactFX(HitSurfaceType);
		if (ImpactFX)
		{
			UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, GetActorLocation(), GetActorRotation());
		}

		// play sound
		USoundCue* ImpactSound = GetImpactSound(HitSurfaceType);
		if (ImpactSound)
		{
			UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
		}

		/*if (DefaultDecal.DecalMaterial)
		{
			FRotator RandomDecalRotation = SurfaceHit.ImpactNormal.Rotation();
			RandomDecalRotation.Roll = FMath::FRandRange(-180.0f, 180.0f);

			UGameplayStatics::SpawnDecalAttached(DefaultDecal.DecalMaterial, FVector(1.0f, DefaultDecal.DecalSize, DefaultDecal.DecalSize),
				SurfaceHit.Component.Get(), SurfaceHit.BoneName,
				SurfaceHit.ImpactPoint, RandomDecalRotation, EAttachLocation::KeepWorldPosition,
				DefaultDecal.LifeSpan);
		}*/
	}
}

UParticleSystem* AXLImpactFX::GetImpactFX(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{
	UParticleSystem* ImpactFX = NULL;

	switch (SurfaceType)
	{
		case XL_SURFACE_Concrete:			ImpactFX = ConcreteFX; break;
		case XL_SURFACE_Dirt:				ImpactFX = DirtFX; break;
		case XL_SURFACE_Water:				ImpactFX = WaterFX; break;
		case XL_SURFACE_Metal:				ImpactFX = MetalFX; break;
		case XL_SURFACE_Wood:				ImpactFX = WoodFX; break;
		case XL_SURFACE_Grass:				ImpactFX = GrassFX; break;
		case XL_SURFACE_Glass:				ImpactFX = GlassFX; break;
		case XL_SURFACE_Flesh:				ImpactFX = FleshFX; break;
		case XL_SURFACE_Energy:				ImpactFX = EnergyFX; break;
		case XL_SURFACE_Bark:				ImpactFX = BarkFX; break;
		case XL_SURFACE_Vegetation:			ImpactFX = VegetationFX; break;
		case XL_SURFACE_Plastic:			ImpactFX = PlasticFX; break;
		default:							ImpactFX = DefaultFX; break;
	}

	return ImpactFX;
}

USoundCue* AXLImpactFX::GetImpactSound(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{
	USoundCue* ImpactSound = NULL;

	switch (SurfaceType)
	{
		case XL_SURFACE_Concrete:			ImpactSound = ConcreteSound; break;
		case XL_SURFACE_Dirt:				ImpactSound = DirtSound; break;
		case XL_SURFACE_Water:				ImpactSound = WaterSound; break;
		case XL_SURFACE_Metal:				ImpactSound = MetalSound; break;
		case XL_SURFACE_Wood:				ImpactSound = WoodSound; break;
		case XL_SURFACE_Grass:				ImpactSound = GrassSound; break;
		case XL_SURFACE_Glass:				ImpactSound = GlassSound; break;
		case XL_SURFACE_Flesh:				ImpactSound = FleshSound; break;
		case XL_SURFACE_Energy:				ImpactSound = EnergySound; break;
		case XL_SURFACE_Bark:				ImpactSound = BarkSound; break;
		case XL_SURFACE_Vegetation:			ImpactSound = VegetationSound; break;
		case XL_SURFACE_Plastic:			ImpactSound = PlasticSound; break;
		default:							ImpactSound = DefaultSound; break;
	}

	return ImpactSound;
}
