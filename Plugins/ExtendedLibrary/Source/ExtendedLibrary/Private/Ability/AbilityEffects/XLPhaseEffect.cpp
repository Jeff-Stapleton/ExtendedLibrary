// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPhaseEffect.h"

UXLPhaseEffect::UXLPhaseEffect()
{
}

void UXLPhaseEffect::Activate(AXLCharacter* Instigator, AXLCharacter* Target, float Strength, float Duration)
{
	if (Instigator && Target)
	{
		Responses.SetResponse(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Ignore);
		Responses.SetResponse(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Ignore);
		Responses.SetResponse(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Block);
		Responses.SetResponse(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Block);

		Target->GetCapsuleComponent()->SetCollisionResponseToChannels(Responses);
		Target->GetMesh()->SetCollisionResponseToChannels(Responses);
	}
}

void UXLPhaseEffect::Deactivate(AXLCharacter* Instigator, AXLCharacter* Target, float Strength, float Duration)
{
	if (Instigator && Target)
	{
		Responses.SetResponse(ECollisionChannel::ECC_GameTraceChannel1, ECollisionResponse::ECR_Block);
		Responses.SetResponse(ECollisionChannel::ECC_GameTraceChannel2, ECollisionResponse::ECR_Block);
		Responses.SetResponse(ECollisionChannel::ECC_GameTraceChannel3, ECollisionResponse::ECR_Ignore);
		Responses.SetResponse(ECollisionChannel::ECC_GameTraceChannel4, ECollisionResponse::ECR_Ignore);

		Target->GetCapsuleComponent()->SetCollisionResponseToChannels(Responses);
		Target->GetMesh()->SetCollisionResponseToChannels(Responses);
	}
}