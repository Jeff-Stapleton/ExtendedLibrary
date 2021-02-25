// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Characters/XLCharacter.h"
#include "Data/XLCharacterAttributeSet.h"
#include "AnimNotifies/XLFootstepNotify.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundBase.h"
#include "Animation/AnimSequenceBase.h"

#if WITH_EDITOR
#include "Logging/MessageLog.h"
#include "Misc/UObjectToken.h"
#endif

UXLFootstepNotify::UXLFootstepNotify() : Super()
{
	VolumeMultiplier = 1.f;
	PitchMultiplier = 1.f;

#if WITH_EDITORONLY_DATA

	NotifyColor = FColor(196, 142, 255, 255);
	bPreviewIgnoreAttenuation = false;

#endif
}

void UXLFootstepNotify::Notify(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	PlaySound(MeshComp, Animation);
}

void UXLFootstepNotify::PlaySound(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation)
{
	if (Sound && MeshComp)
	{
		if (Sound->IsLooping())
		{
			UE_LOG(LogAudio, Warning, TEXT("PlaySound notify: Anim %s tried to spawn infinitely looping sound asset %s. Spawning suppressed."), *GetNameSafe(Animation), *GetNameSafe(Sound));
			return;
		}

#if WITH_EDITORONLY_DATA
		UWorld* World = MeshComp->GetWorld();
		if (bPreviewIgnoreAttenuation && World && World->WorldType == EWorldType::EditorPreview)
		{
			UGameplayStatics::PlaySound2D(World, Sound, VolumeMultiplier, PitchMultiplier);
		}
		else
#endif
		{
			if (bFollow)
			{
				UGameplayStatics::SpawnSoundAttached(Sound, MeshComp, AttachName, FVector(ForceInit), EAttachLocation::SnapToTarget, false, VolumeMultiplier, PitchMultiplier);
			}
			else
			{
				float AdjustedVolumeMultiplier = VolumeMultiplier;
				AXLCharacter* Character = Cast<AXLCharacter>(MeshComp->GetOwner());
				if (Character)
				{
					AdjustedVolumeMultiplier *= Character->CharacterAttributes->GetVolumeMultiplier();
				}
				UGameplayStatics::PlaySoundAtLocation(MeshComp->GetWorld(), Sound, MeshComp->GetComponentLocation(), AdjustedVolumeMultiplier, PitchMultiplier);
			}
		}
	}
}

#if WITH_EDITOR
void UXLFootstepNotify::ValidateAssociatedAssets()
{
	static const FName NAME_AssetCheck("AssetCheck");

	if ((Sound != nullptr) && (Sound->IsLooping()))
	{
		UObject* ContainingAsset = GetContainingAsset();

		FMessageLog AssetCheckLog(NAME_AssetCheck);

		const FText MessageLooping = FText::Format(
			NSLOCTEXT("AnimNotify", "Sound_ShouldNotLoop", "Sound {0} used in anim notify for asset {1} is set to looping, but the slot is a one-shot (it won't be played to avoid leaking an instance per notify)."),
			FText::AsCultureInvariant(Sound->GetPathName()),
			FText::AsCultureInvariant(ContainingAsset->GetPathName()));
		AssetCheckLog.Warning()
			->AddToken(FUObjectToken::Create(ContainingAsset))
			->AddToken(FTextToken::Create(MessageLooping));

		if (GIsEditor)
		{
			AssetCheckLog.Notify(MessageLooping, EMessageSeverity::Warning, /*bForce=*/ true);
		}
	}
}
#endif