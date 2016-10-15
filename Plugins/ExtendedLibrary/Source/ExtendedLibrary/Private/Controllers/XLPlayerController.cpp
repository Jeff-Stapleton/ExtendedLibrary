// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLPlayerController.h"

AXLPlayerController::AXLPlayerController()
{
	SetActorTickEnabled(true);
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AXLPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AXLPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

}

void AXLPlayerController::SetPlayer(UPlayer* InPlayer)
{
	Super::SetPlayer(InPlayer);

	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
}

void AXLPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAxis("Move", this, &AXLPlayerController::Move);
	InputComponent->BindAxis("Strafe", this, &AXLPlayerController::Strafe);

	InputComponent->BindAxis("Turn", this, &AXLPlayerController::Turn);
	InputComponent->BindAxis("Look", this, &AXLPlayerController::Look);

	InputComponent->BindAction("Jump", IE_Pressed, this, &AXLPlayerController::Jump);

	InputComponent->BindAction("Dodge", IE_Pressed, this, &AXLPlayerController::Dodge);

	InputComponent->BindAction("Sprint", IE_Pressed, this, &AXLPlayerController::StartSprint);
	InputComponent->BindAction("Sprint", IE_Released, this, &AXLPlayerController::StopSprint);

	InputComponent->BindAction("Attack", IE_Pressed, this, &AXLPlayerController::StartAttack);
	InputComponent->BindAction("Attack", IE_Released, this, &AXLPlayerController::StopAttack);

	InputComponent->BindAction("Reload", IE_Pressed, this, &AXLPlayerController::Reload);

	InputComponent->BindAction("Melee", IE_Pressed, this, &AXLPlayerController::Melee);
}

void AXLPlayerController::Move(float Direction)
{
	if (XLControllerCan::Move(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->Move(Direction);
	}
}

void AXLPlayerController::Strafe(float Direction)
{
	if (XLControllerCan::Strafe(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->Strafe(Direction);
	}
}

void AXLPlayerController::Turn(float Direction)
{
	if (XLControllerCan::Turn(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->Turn(Direction);
	}
}

void AXLPlayerController::Look(float Direction)
{
	if (XLControllerCan::Look(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->Look(Direction);
	}
}

void AXLPlayerController::Jump()
{
	if (XLControllerCan::Jump(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->Jump();
	}
}

void AXLPlayerController::Dodge()
{
	
}

void AXLPlayerController::StartSprint()
{
	if (XLControllerCan::StartSprint(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->StartSprint();
	}
}

void AXLPlayerController::StopSprint()
{
	if (XLControllerCan::StopSprint(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->StopSprint();
	}
}

void AXLPlayerController::StartAttack()
{
	if (XLControllerCan::StartAttack(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->StartAttack();
	}
}

void AXLPlayerController::StopAttack()
{
	if (XLControllerCan::StopAttack(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->StopAttack();
	}
}

void AXLPlayerController::Reload()
{
	if (XLControllerCan::Reload(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->Reload();
	}
}

void AXLPlayerController::Melee()
{
	if (XLControllerCan::Melee(this))
	{
		(Cast<AXLCharacter>(GetPawn()))->Melee();
	}
}

void AXLPlayerController::UnFreeze()
{
	ServerRestartPlayer();
}

void AXLPlayerController::Reset()
{
	Super::Reset();
}

void AXLPlayerController::ClientGameStarted()
{
	/*AXLHUD* XLHUD = GetXLHUD();
	if (XLHUD)
	{
	XLHUD->SetMatchState(EXLMatchState::Playing);
	}

	QueryAchievements();*/
}

void AXLPlayerController::ClientStartOnlineGame()
{
	if (!IsPrimaryPlayer())
		return;

	AXLPlayerState* CharacterState = Cast<AXLPlayerState>(PlayerState);
	if (CharacterState)
	{
		IOnlineSubsystem* OnlineSub = IOnlineSubsystem::Get();
		if (OnlineSub)
		{
			IOnlineSessionPtr Sessions = OnlineSub->GetSessionInterface();
			if (Sessions.IsValid())
			{
				UE_LOG(LogOnline, Log, TEXT("Starting session %s on client"), *CharacterState->SessionName.ToString());
				Sessions->StartSession(CharacterState->SessionName);
			}
		}
	}
	else
	{
		// Keep retrying until player state is replicated
		GetWorld()->GetTimerManager().SetTimer(StartGame_Timer, FTimerDelegate::CreateUObject(this, &AXLPlayerController::ClientStartOnlineGame), 0.2f, false);
	}
}


