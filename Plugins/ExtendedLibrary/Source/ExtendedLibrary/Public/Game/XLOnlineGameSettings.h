// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

#pragma once

/**
* General session settings for a arena game
*/
class FXLOnlineSessionSettings : public FOnlineSessionSettings
{
public:

	FXLOnlineSessionSettings(bool bIsLAN = false, bool bIsPresence = false, int32 MaxNumPlayers = 4);
	virtual ~FXLOnlineSessionSettings() {}
};

/**
* General search setting for a arena game
*/
class FXLOnlineSearchSettings : public FOnlineSessionSearch
{
public:
	FXLOnlineSearchSettings(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FXLOnlineSearchSettings() {}
};

/**
* Search settings for an empty dedicated server to host a match
*/
class FXLOnlineSearchSettingsEmptyDedicated : public FXLOnlineSearchSettings
{
public:
	FXLOnlineSearchSettingsEmptyDedicated(bool bSearchingLAN = false, bool bSearchingPresence = false);

	virtual ~FXLOnlineSearchSettingsEmptyDedicated() {}
};