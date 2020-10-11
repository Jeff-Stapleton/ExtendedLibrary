#include "ExtendedLibraryPCH.h"
#include "Weapons/XLRangedWeapon.h"
#include "Managers/XLPlayerCameraManager.h"
#include "Weapons/Components/XLADSComponent.h"

UXLADSComponent::UXLADSComponent()
{
	bWantsInitializeComponent = true;
	SetIsReplicatedByDefault(true);
}

void UXLADSComponent::InitializeComponent()
{
	Super::InitializeComponent();

	//Owner = Cast<AXLRangedWeapon>(GetOwner());

	GetWeapon()->ItemSecondaryStateDelegate.AddDynamic(this, &UXLADSComponent::DetermineAction);
	//GetWeapon()->CharacterDeathDelegate.AddDynamic(this, &UXLADSComponent::StopAim);
}

void UXLADSComponent::DetermineAction()
{
	if (GetWeapon()->SecondaryState == EItemSecondaryState::ADS)
	{
		StartAim();
	}
	else
	{
		StopAim();
	}
}

void UXLADSComponent::StartAim_Implementation()
{
	Character = Cast<AXLCharacter>(GetWeapon()->Character);
	if (Character)
	{
		Controller = Cast<AXLPlayerController>(Character->GetController());
		if (Controller)
		{
			CameraManager = Cast<AXLPlayerCameraManager>(Controller->PlayerCameraManager);

			if (ScopeWidgetBP)
			{
				ScopeWidget = CreateWidget<UUserWidget>(GetWorld(), ScopeWidgetBP);
				ScopeWidget->AddToViewport();
			}

			if (CameraManager)
			{
				CameraManager->FOVSpeed = Speed;
				CameraManager->TargetFOV = FOV;
			}
		}
	}
}

void UXLADSComponent::StopAim_Implementation()
{
	if (GetWeapon()->Character)
	{
		Character = Cast<AXLCharacter>(GetWeapon()->Character);
		if (Character->GetController())
		{
			Controller = Cast<AXLPlayerController>(Character->GetController());
			if (Controller->PlayerCameraManager)
			{
				CameraManager = Cast<AXLPlayerCameraManager>(Controller->PlayerCameraManager);
				CameraManager->FOVSpeed = Speed;
				CameraManager->TargetFOV = CameraManager->NormalFOV;
			}
		}
	}
	
	if (ScopeWidget->IsValidLowLevelFast())
	{
		ScopeWidget->RemoveFromParent();
	}
}
