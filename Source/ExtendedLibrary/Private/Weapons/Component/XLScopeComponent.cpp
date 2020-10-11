#include "ExtendedLibraryPCH.h"
#include "Weapons/XLRangedWeapon.h"
#include "Managers/XLPlayerCameraManager.h"
#include "Weapons/Components/XLScopeComponent.h"

UXLScopeComponent::UXLScopeComponent()
{
	SetIsReplicatedByDefault(true);
	bWantsInitializeComponent = true;
}


void UXLScopeComponent::InitializeComponent()
{
	Super::InitializeComponent();

	Owner = Cast<AXLRangedWeapon>(GetOwner());

	//Owner->TargetingStateDelegate.AddDynamic(this, &UXLScopeComponent::DetermineAction);
	//Owner->CharacterDeathDelegate.AddDynamic(this, &UXLScopeComponent::StopAim);
}

void UXLScopeComponent::DetermineAction()
{
	if (Owner->SecondaryState == EItemSecondaryState::ADS)
	{
		StartAim();
	}
	else
	{
		StopAim();
	}
}

void UXLScopeComponent::StartAim_Implementation()
{
	Character = Cast<AXLCharacter>(Owner->Character);
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

				Character->GetMesh()->SetOwnerNoSee(true);
				Owner->Mesh3P->SetOwnerNoSee(true);
			}

			if (CameraManager)
			{
				CameraManager->FOVSpeed = Speed;
				CameraManager->TargetFOV = FOV;
			}
		}
	}
}

void UXLScopeComponent::StopAim_Implementation()
{
	Character = Cast<AXLCharacter>(Owner->Character);
	Controller = Cast<AXLPlayerController>(Character->GetController());
	CameraManager = Cast<AXLPlayerCameraManager>(Controller->PlayerCameraManager);
	
	if (ScopeWidget)
	{
		ScopeWidget->RemoveFromParent();
		Character->GetMesh()->SetOwnerNoSee(false);
		Owner->Mesh3P->SetOwnerNoSee(false);
	}

	CameraManager->FOVSpeed = Speed;
	CameraManager->TargetFOV = CameraManager->NormalFOV;
}
