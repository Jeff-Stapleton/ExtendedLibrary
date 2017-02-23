// Fill out your copyright notice in the Description page of Project Settings.

#include "ExtendedLibraryPCH.h"
#include "XLGameInstance.h"

UXLGameInstance::UXLGameInstance()
{
}

bool UXLGameInstance::Tick(float DeltaSeconds)
{
	/*if (Sessions.IsValid())
	{
		EOnlineSessionState::Type SessionState = Sessions->GetSessionState(GameSessionName);

		if (SessionState == EOnlineSessionState::NoSession)
		{
			ULocalPlayer * NewPlayerOwner = GetFirstGamePlayer();

			if (NewPlayerOwner != nullptr)
			{
				NewPlayerOwner->SetControllerId(PendingInvite.ControllerId);
				NewPlayerOwner->SetCachedUniqueNetId(PendingInvite.UserId);
				SetIsOnline(true);
				JoinSession(NewPlayerOwner, PendingInvite.InviteResult);
			}

			PendingInvite.UserId.Reset();
		}
	}*/
	return true;
}

void UXLGameInstance::Init()
{
	Super::Init();

}

void UXLGameInstance::Shutdown()
{
	Super::Shutdown();

	// Unregister ticker delegate
	//FTicker::GetCoreTicker().RemoveTicker(TickDelegateHandle);
}

void UXLGameInstance::StartGameInstance()
{
}

/*void UXLGameInstance::OnJoinSessionComplete(EOnJoinSessionCompleteResult::Type Result)
{
	// Add the splitscreen player if one exists
	if (Result == EOnJoinSessionCompleteResult::Success && LocalPlayers.Num() > 1)
	{
		auto Sessions = Online::GetSessionInterface();
		if (Sessions.IsValid() && LocalPlayers[1]->GetPreferredUniqueNetId().IsValid())
		{
			Sessions->RegisterLocalPlayer(*LocalPlayers[1]->GetPreferredUniqueNetId(), GameSessionName, FOnRegisterLocalPlayerCompleteDelegate::CreateUObject(this, &UShooterGameInstance::OnRegisterJoiningLocalPlayerComplete));
		}
	}
	else
	{
		// We either failed or there is only a single local user
		FinishJoinSession(Result);
	}
}

void UXLGameInstance::FinishJoinSession(EOnJoinSessionCompleteResult::Type Result)
{
	if (Result != EOnJoinSessionCompleteResult::Success)
	{
		FText ReturnReason;
		switch (Result)
		{
		case EOnJoinSessionCompleteResult::SessionIsFull:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Game is full.");
			break;
		case EOnJoinSessionCompleteResult::SessionDoesNotExist:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Game no longer exists.");
			break;
		default:
			ReturnReason = NSLOCTEXT("NetworkErrors", "JoinSessionFailed", "Join failed.");
			break;
		}

		FText OKButton = NSLOCTEXT("DialogButtons", "OKAY", "OK");
		RemoveNetworkFailureHandlers();
		ShowMessageThenGoMain(ReturnReason, OKButton, FText::GetEmpty());
		return;
	}

	InternalTravelToSession(GameSessionName);
}

bool UXLGameInstance::JoinSession(ULocalPlayer* LocalPlayer, const FOnlineSessionSearchResult& SearchResult)
{
	// needs to tear anything down based on current state?
	AShooterGameSession* const GameSession = GetGameSession();
	if (GameSession)
	{
		AddNetworkFailureHandlers();

		OnJoinSessionCompleteDelegateHandle = GameSession->OnJoinSessionComplete().AddUObject(this, &UShooterGameInstance::OnJoinSessionComplete);
		if (GameSession->JoinSession(LocalPlayer->GetPreferredUniqueNetId(), GameSessionName, SearchResult))
		{
			// If any error occured in the above, pending state would be set
			if ((PendingState == CurrentState) || (PendingState == ShooterGameInstanceState::None))
			{
				// Go ahead and go into loading state now
				// If we fail, the delegate will handle showing the proper messaging and move to the correct state
				ShowLoadingScreen();
				GotoState(ShooterGameInstanceState::Playing);
				return true;
			}
		}
	}

	return false;
}*/


