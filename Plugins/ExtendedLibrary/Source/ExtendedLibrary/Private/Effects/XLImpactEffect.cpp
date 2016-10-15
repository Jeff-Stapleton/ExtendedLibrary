// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLImpactEffect.h"

AXLImpactEffect::AXLImpactEffect()
{
	PrimaryActorTick.bCanEverTick = true;

	ImpactLight = CreateDefaultSubobject<UPointLightComponent>(TEXT("Impact Effect"));
	RootComponent = ImpactLight;
	ImpactLight->AttenuationRadius = 400.0;
	ImpactLight->Intensity = 500.0f;
	ImpactLight->bUseInverseSquaredFalloff = false;
	ImpactLight->LightColor = FColor(255, 185, 35);
	ImpactLight->CastShadows = false;
	ImpactLight->bVisible = true;

	ImpactLightFadeOut = 0.2f;
}

void AXLImpactEffect::BeginPlay()
{
	Super::BeginPlay();

	UPhysicalMaterial* HitPhysMat = SurfaceHit.PhysMaterial.Get();
	EPhysicalSurface HitSurfaceType = UPhysicalMaterial::DetermineSurfaceType(HitPhysMat);

	// show particles
	UParticleSystem* ImpactFX = GetImpactFX(HitSurfaceType);
	if (ImpactFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, ImpactFX, GetActorLocation(), GetActorRotation());
	}

	// play sound
	USoundBase* ImpactSound = GetImpactSound(HitSurfaceType);
	if (ImpactSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation());
	}

	if (DefaultDecal.DecalMaterial)
	{
		FRotator RandomDecalRotation = SurfaceHit.ImpactNormal.Rotation();
		RandomDecalRotation.Roll = FMath::FRandRange(-180.0f, 180.0f);

		UGameplayStatics::SpawnDecalAttached(DefaultDecal.DecalMaterial, FVector(DefaultDecal.DecalSize, DefaultDecal.DecalSize, 1.0f),
			SurfaceHit.Component.Get(), SurfaceHit.BoneName,
			SurfaceHit.ImpactPoint, RandomDecalRotation, EAttachLocation::KeepWorldPosition,
			DefaultDecal.LifeSpan);
	}
}

UParticleSystem* AXLImpactEffect::GetImpactFX(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{

	UParticleSystem* ImpactFX = NULL;

	switch (SurfaceType)
	{

	case XL_SURFACE_Concrete:	ImpactFX = ConcreteFX; break;
	case XL_SURFACE_Dirt:		ImpactFX = DirtFX; break;
	case XL_SURFACE_Water:		ImpactFX = WaterFX; break;
	case XL_SURFACE_Metal:		ImpactFX = MetalFX; break;
	case XL_SURFACE_Wood:		ImpactFX = WoodFX; break;
	case XL_SURFACE_Grass:		ImpactFX = GrassFX; break;
	case XL_SURFACE_Glass:		ImpactFX = GlassFX; break;
	case XL_SURFACE_Flesh:		ImpactFX = FleshFX; break;
	case XL_SURFACE_Energy:		ImpactFX = EnergyFX; break;

	default:						ImpactFX = DefaultFX; break;
	}

	return ImpactFX;

}

USoundBase* AXLImpactEffect::GetImpactSound(TEnumAsByte<EPhysicalSurface> SurfaceType) const
{

	USoundBase* ImpactSound = NULL;

	switch (SurfaceType)
	{
	case XL_SURFACE_Concrete:	ImpactSound = ConcreteSound; break;
	case XL_SURFACE_Dirt:		ImpactSound = DirtSound; break;
	case XL_SURFACE_Water:		ImpactSound = WaterSound; break;
	case XL_SURFACE_Metal:		ImpactSound = MetalSound; break;
	case XL_SURFACE_Wood:		ImpactSound = WoodSound; break;
	case XL_SURFACE_Grass:		ImpactSound = GrassSound; break;
	case XL_SURFACE_Glass:		ImpactSound = GlassSound; break;
	case XL_SURFACE_Flesh:		ImpactSound = FleshSound; break;
	case XL_SURFACE_Energy:		ImpactSound = EnergySound; break;

	default:						ImpactSound = DefaultSound; break;
	}

	return ImpactSound;

}

void AXLImpactEffect::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const float TimeAlive = GetWorld()->GetTimeSeconds() - CreationTime;
	const float TimeRemaining = FMath::Max(0.0f, ImpactLightFadeOut - TimeAlive);

	if (TimeRemaining > 0)
	{
		const float FadeAlpha = 1.0f - FMath::Square(TimeRemaining / ImpactLightFadeOut);

		UPointLightComponent* DefLight = Cast<UPointLightComponent>(GetClass()->GetDefaultSubobjectByName(ImpactLightComponentName));
		//ImpactLight->SetBrightness(DefLight->Intensity * FadeAlpha);
	}
	else
	{
		Destroy();
	}
}
