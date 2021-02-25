// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/ObjectMacros.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "XLFootstepNotify.generated.h"

class UAnimSequenceBase;
class USkeletalMeshComponent;
class USoundBase;

UCLASS(const, hidecategories = Object, collapsecategories, Config = Game, meta = (DisplayName = "Footstep"))
class EXTENDEDLIBRARY_API UXLFootstepNotify : public UAnimNotify
{
	GENERATED_BODY()

public: 

	// Sound to Play
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	USoundBase* Sound;

	// Volume Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	float VolumeMultiplier;

	// Pitch Multiplier
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (ExposeOnSpawn = true))
	float PitchMultiplier;

	// If this sound should follow its owner
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify")
	uint32 bFollow : 1;

	// Socket or bone name to attach sound to
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AnimNotify", meta = (EditCondition = "bFollow", ExposeOnSpawn = true))
	FName AttachName;

#if WITH_EDITORONLY_DATA

	UPROPERTY(Config, EditAnywhere, Category = "AnimNotify")
	uint32 bPreviewIgnoreAttenuation : 1;

#endif

public: 

	UXLFootstepNotify();

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	virtual void PlaySound(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation);

#if WITH_EDITOR

	virtual void ValidateAssociatedAssets() override;

#endif
};
