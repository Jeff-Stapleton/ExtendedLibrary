// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "Managers/XLInventoryManager.h"
#include "Items/XLItem.h"
#include "Controllers/XLPlayerController.h"
#include "Controllers/InputComponents/XLCharacterInputComponent.h"

UXLCharacterInputComponent::UXLCharacterInputComponent()
{
}

void UXLCharacterInputComponent::Init(APlayerController* NewController)
{
	RegisterComponent();
	bBlockInput = false;
	Priority = 0;

	Controller = Cast<AXLPlayerController>(NewController);

	BindAction("ToggleCamera", IE_Pressed, this, &UXLCharacterInputComponent::ToggleCamera);

	BindAxis("Move", this, &UXLCharacterInputComponent::Move);
	BindAxis("Strafe", this, &UXLCharacterInputComponent::Strafe);

	BindAxis("Turn", this, &UXLCharacterInputComponent::Turn);
	BindAxis("Look", this, &UXLCharacterInputComponent::Look);

	BindAction("Jump", IE_Pressed, this, &UXLCharacterInputComponent::Jump);

	BindAction("Interact", IE_Pressed, this, &UXLCharacterInputComponent::Interact);

	BindAction("Crouch", IE_Pressed, this, &UXLCharacterInputComponent::StartCrouch);
	BindAction("Crouch", IE_Released, this, &UXLCharacterInputComponent::StopCrouch);

	BindAction("Sprint", IE_Pressed, this, &UXLCharacterInputComponent::StartSprint);
	BindAction("Sprint", IE_Released, this, &UXLCharacterInputComponent::StopSprint);

	BindAction("EquipItem", IE_Released, this, &UXLCharacterInputComponent::EquipItem);
	BindAction("StowItem", IE_Released, this, &UXLCharacterInputComponent::StowItem);

	BindAction("ItemPrimary", IE_Pressed, this, &UXLCharacterInputComponent::StartActivateItemPrimary);
	BindAction("ItemPrimary", IE_Released, this, &UXLCharacterInputComponent::StopActivateItemPrimary);

	BindAction("ItemSecondary", IE_Pressed, this, &UXLCharacterInputComponent::StartActivateItemSecondary);
	BindAction("ItemSecondary", IE_Released, this, &UXLCharacterInputComponent::StopActivateItemSecondary);
}

void UXLCharacterInputComponent::Move(float Direction)
{
	if (XLControllerCan::Move(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->Move(Direction);
	}
}

void UXLCharacterInputComponent::Strafe(float Direction)
{
	if (XLControllerCan::Strafe(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->Strafe(Direction);
	}
}

void UXLCharacterInputComponent::Turn(float Direction)
{
	if (XLControllerCan::Turn(Controller))
	{
		//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("CONTROLLER Direction: %f"), Direction));
		(Cast<AXLCharacter>(Controller->GetPawn()))->Turn(Direction);
	}
}

void UXLCharacterInputComponent::Look(float Direction)
{
	if (XLControllerCan::Look(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->Look(-Direction);
	}
}

void UXLCharacterInputComponent::ToggleCamera()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Controller->TogglePerspective();
	}
}

void UXLCharacterInputComponent::Interact()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->Interact();
	}
}

void UXLCharacterInputComponent::Jump()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->ActivateAbilityById("Action.Jump");
	}
}

void UXLCharacterInputComponent::StartCrouch()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->ActivateAbilityById("Action.Crouch");
	}
}
void UXLCharacterInputComponent::StopCrouch()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->EndAbilityById("Action.Crouch");
	}
}

void UXLCharacterInputComponent::StartSprint()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->ActivateAbilityById("Action.Sprint");
	}
}
void UXLCharacterInputComponent::StopSprint()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->EndAbilityById("Action.Sprint");
	}
}

void UXLCharacterInputComponent::EquipItem()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		if (Character && Character->CurrentItem)
		{
			AXLItem* Item = Character->CharacterInventory->GetItem(0);
			if (Item)
			{
				Character->EquipItem(Item, "Hand_R");
			}
		}
	}
}
void UXLCharacterInputComponent::StowItem()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		if (Character && Character->CurrentItem)
		{
			Character->StowItem(Character->CurrentItem, Character->CurrentItem->StowedMesh3P, Character->CurrentItem->StowedMesh1P, Character->CurrentItem->Socket);
		}
	}
}

void UXLCharacterInputComponent::StartActivateItemPrimary()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->ActivateAbilityById("Item.Primary");
	}
}
void UXLCharacterInputComponent::StopActivateItemPrimary()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->EndAbilityById("Item.Primary");
	}
}

void UXLCharacterInputComponent::StartActivateItemSecondary()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->ActivateAbilityById("Item.Secondary");
	}
}
void UXLCharacterInputComponent::StopActivateItemSecondary()
{
	AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
	if (Character && Character->CurrentItem)
	{
		Character->EndAbilityById("Item.Secondary");
	}
}
