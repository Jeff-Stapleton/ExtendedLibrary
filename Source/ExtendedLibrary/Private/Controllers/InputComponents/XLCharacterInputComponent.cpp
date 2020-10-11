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

	BindAction("Dodge", IE_Pressed, this, &UXLCharacterInputComponent::Dodge);

	BindAction("Interact", IE_Pressed, this, &UXLCharacterInputComponent::Interact);

	BindAction("Crouch", IE_Pressed, this, &UXLCharacterInputComponent::StartCrouch);
	BindAction("Crouch", IE_Released, this, &UXLCharacterInputComponent::StopCrouch);

	BindAction("Prone", IE_Pressed, this, &UXLCharacterInputComponent::StartProne);
	BindAction("Prone", IE_Released, this, &UXLCharacterInputComponent::StopProne);

	BindAction("Sprint", IE_Pressed, this, &UXLCharacterInputComponent::StartSprint);
	BindAction("Sprint", IE_Released, this, &UXLCharacterInputComponent::StopSprint);

	BindAction("EquipItem", IE_Released, this, &UXLCharacterInputComponent::EquipItem);
	BindAction("StowItem", IE_Released, this, &UXLCharacterInputComponent::StowItem);

	//BindAction("NextWeapon", IE_Released, this, &UXLCharacterInputComponent::NextWeapon);
	//BindAction("PreviousWeapon", IE_Released, this, &UXLCharacterInputComponent::PreviousWeapon);

	BindAction("FirstWeapon", IE_Released, this, &UXLCharacterInputComponent::FirstWeapon);
	BindAction("SecondWeapon", IE_Released, this, &UXLCharacterInputComponent::SecondWeapon);
	BindAction("ThirdWeapon", IE_Released, this, &UXLCharacterInputComponent::ThirdWeapon);
	BindAction("FourthWeapon", IE_Released, this, &UXLCharacterInputComponent::FourthWeapon);
	BindAction("FifthWeapon", IE_Released, this, &UXLCharacterInputComponent::FifthWeapon);
	BindAction("SixthWeapon", IE_Released, this, &UXLCharacterInputComponent::SixthWeapon);
	BindAction("SeventhWeapon", IE_Released, this, &UXLCharacterInputComponent::SeventhWeapon);
	BindAction("EighthWeapon", IE_Released, this, &UXLCharacterInputComponent::EighthWeapon);

	BindAction("PrimaryAction", IE_Pressed, this, &UXLCharacterInputComponent::ActivatePrimary);
	BindAction("PrimaryAction", IE_Released, this, &UXLCharacterInputComponent::DeactivatePrimary);

	BindAction("SecondaryAction", IE_Pressed, this, &UXLCharacterInputComponent::ActivateSecondary);
	BindAction("SecondaryAction", IE_Released, this, &UXLCharacterInputComponent::DeactivatedSecondary);

	BindAction("TertiaryAction", IE_Pressed, this, &UXLCharacterInputComponent::ActivateTertiary);
	BindAction("TertiaryAction", IE_Released, this, &UXLCharacterInputComponent::DeactivateTertiary);

	BindAction("Melee", IE_Pressed, this, &UXLCharacterInputComponent::Melee);

	BindAction("Ability1", IE_Pressed, this, &UXLCharacterInputComponent::StartAbility1);
	BindAction("Ability1", IE_Released, this, &UXLCharacterInputComponent::StopAbility1);

	BindAction("Ability2", IE_Pressed, this, &UXLCharacterInputComponent::StartAbility2);
	BindAction("Ability2", IE_Released, this, &UXLCharacterInputComponent::StopAbility2);

	BindAction("Ability3", IE_Pressed, this, &UXLCharacterInputComponent::StartAbility3);
	BindAction("Ability3", IE_Released, this, &UXLCharacterInputComponent::StopAbility3);
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
	if (XLControllerCan::Jump(Controller))
	{
		Controller->TogglePerspective();
	}
}

void UXLCharacterInputComponent::Interact()
{
	if (XLControllerCan::StartSprint(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->Interact();
	}
}

void UXLCharacterInputComponent::Jump()
{
	if (XLControllerCan::Jump(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->Jump();
	}
}

void UXLCharacterInputComponent::Dodge()
{

}

void UXLCharacterInputComponent::StartCrouch()
{
	if (XLControllerCan::StartCrouch(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StartCrouch();
	}
}
void UXLCharacterInputComponent::StopCrouch()
{
	if (XLControllerCan::StopCrouch(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StopCrouch();
	}
}

void UXLCharacterInputComponent::StartProne()
{
	if (XLControllerCan::StartProne(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StartProne();
	}
}
void UXLCharacterInputComponent::StopProne()
{
	if (XLControllerCan::StopProne(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StopProne();
	}
}

void UXLCharacterInputComponent::StartSprint()
{
	if (XLControllerCan::StartSprint(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StartSprint();
	}
}
void UXLCharacterInputComponent::StopSprint()
{
	if (XLControllerCan::StopSprint(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StopSprint();
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

//void UXLCharacterInputComponent::NextWeapon()
//{
//	if (XLControllerCan::Jump(Controller))
//	{
//		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
//
//		uint32 CurrentIndex = Character->CurrentItem;
//		uint32 NextIndex = Character->CharacterWeapons->GetNextWeaponIndex(CurrentIndex);
//		Character->EquipItem(NextIndex);
//	}
//}
//void UXLCharacterInputComponent::PreviousWeapon()
//{
//	if (XLControllerCan::Jump(Controller))
//	{
//		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
//
//		uint32 CurrentIndex = Character->CurrentItem;
//		uint32 PreviousIndex = Character->CharacterWeapons->GetPreviousWeaponIndex(CurrentIndex);
//		Character->EquipItem(PreviousIndex);
//	}
//}

void UXLCharacterInputComponent::FirstWeapon()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		AXLItem* Item = Character->CharacterInventory->GetItem(0);
		if (Character->CurrentItem)
		{
			Character->SwitchItem(Item);
		}
		else
		{
    Character->EquipItem(Item, "Hand_R");
		}
	}
}
void UXLCharacterInputComponent::SecondWeapon()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		AXLItem* Item = Character->CharacterInventory->GetItem(1);
		if (Character->CurrentItem)
		{
			Character->SwitchItem(Item);
		}
		else
		{
    Character->EquipItem(Item, "Hand_R");
		}
	}
}
void UXLCharacterInputComponent::ThirdWeapon()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		AXLItem* Item = Character->CharacterInventory->GetItem(2);
		if (Character->CurrentItem)
		{
			Character->SwitchItem(Item);
		}
		else
		{
    Character->EquipItem(Item, "Hand_R");
		}
	}
}
void UXLCharacterInputComponent::FourthWeapon()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		AXLItem* Item = Character->CharacterInventory->GetItem(3);
		if (Character->CurrentItem)
		{
			Character->SwitchItem(Item);
		}
		else
		{
    Character->EquipItem(Item, "Hand_R");
		}
	}
}
void UXLCharacterInputComponent::FifthWeapon()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		AXLItem* Item = Character->CharacterInventory->GetItem(4);
		if (Character->CurrentItem)
		{
			Character->SwitchItem(Item);
		}
		else
		{
    Character->EquipItem(Item, "Hand_R");
		}
	}
}
void UXLCharacterInputComponent::SixthWeapon()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		AXLItem* Item = Character->CharacterInventory->GetItem(5);
		if (Character->CurrentItem)
		{
			Character->SwitchItem(Item);
		}
		else
		{
    Character->EquipItem(Item, "Hand_R");
		}
	}
}
void UXLCharacterInputComponent::SeventhWeapon()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		AXLItem* Item = Character->CharacterInventory->GetItem(6);
		if (Character->CurrentItem)
		{
			Character->SwitchItem(Item);
		}
		else
		{
    Character->EquipItem(Item, "Hand_R");
		}
	}
}
void UXLCharacterInputComponent::EighthWeapon()
{
	if (XLControllerCan::Jump(Controller))
	{
		AXLCharacter* Character = Cast<AXLCharacter>(Controller->GetPawn());
		AXLItem* Item = Character->CharacterInventory->GetItem(7);
		if (Character->CurrentItem)
		{
			Character->SwitchItem(Item);
		}
		else
		{
			Character->EquipItem(Item, "Hand_R");
		}
	}
}

void UXLCharacterInputComponent::ActivatePrimary()
{
	if (XLControllerCan::StartAttack(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StartItemPrimaryActivate();
	}
}
void UXLCharacterInputComponent::DeactivatePrimary()
{
	if (XLControllerCan::StopAttack(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StopItemPrimaryActivate();
	}
}

void UXLCharacterInputComponent::ActivateSecondary()
{
	if (XLControllerCan::StartAttack(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StartItemSecondaryActivate();
	}
}
void UXLCharacterInputComponent::DeactivatedSecondary()
{
	if (XLControllerCan::StopAttack(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StopItemSecondaryActivate();
	}
}

void UXLCharacterInputComponent::ActivateTertiary()
{
	if (XLControllerCan::Reload(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StartItemTertiaryActivate();
	}
}
void UXLCharacterInputComponent::DeactivateTertiary()
{
	if (XLControllerCan::Reload(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->StopItemTertiaryActivate();
	}
}

void UXLCharacterInputComponent::Melee()
{
	if (XLControllerCan::Melee(Controller))
	{
		(Cast<AXLCharacter>(Controller->GetPawn()))->Melee();
	}
}

void UXLCharacterInputComponent::StartAbility1()
{
	(Cast<AXLCharacter>(Controller->GetPawn()))->StartAbility(0);
}
void UXLCharacterInputComponent::StopAbility1()
{
	(Cast<AXLCharacter>(Controller->GetPawn()))->StopAbility(0);
}
void UXLCharacterInputComponent::StartAbility2()
{
	(Cast<AXLCharacter>(Controller->GetPawn()))->StartAbility(1);
}
void UXLCharacterInputComponent::StopAbility2()
{
	(Cast<AXLCharacter>(Controller->GetPawn()))->StopAbility(1);
}
void UXLCharacterInputComponent::StartAbility3()
{
	(Cast<AXLCharacter>(Controller->GetPawn()))->StartAbility(2);
}
void UXLCharacterInputComponent::StopAbility3()
{
	(Cast<AXLCharacter>(Controller->GetPawn()))->StopAbility(2);
}
