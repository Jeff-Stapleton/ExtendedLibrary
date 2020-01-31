#include "ExtendedLibraryPCH.h"
#include "XLADSComponent.h"

UXLADSComponent::UXLADSComponent()
{
	bWantsInitializeComponent = true;
}


void UXLADSComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Owner = Cast<AXLRangedWeapon>(GetOwner());

	Owner->TargetingStateDelegate.AddDynamic(this, &UXLADSComponent::DetermineAction);
}

void UXLADSComponent::DetermineAction()
{
	Character = Cast<AXLCharacter>(Owner->Character);
	Controller = Cast<AXLPlayerController>(Character->GetController());
	CameraManager = Cast<AXLPlayerCameraManager>(Controller->PlayerCameraManager);

	if (Owner->TargetingState == ETargetingState::ADS)
	{
		CameraManager->FOVSpeed = Speed;
		CameraManager->TargetFOV = FOV;
	}
	else
	{
		CameraManager->FOVSpeed = Speed;
		CameraManager->TargetFOV = CameraManager->NormalFOV;
	}
}

