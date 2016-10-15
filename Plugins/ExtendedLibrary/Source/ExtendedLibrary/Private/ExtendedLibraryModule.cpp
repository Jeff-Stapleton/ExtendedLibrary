/*
	Rahs Tool Suite 1.0.0
	-----
	SaxonRah - Robert Chubb @ ParabolicLabs - 30/11/2014 - 3:36 AM
*/
#include "ExtendedLibraryPCH.h"
#include "ExtendedLibraryModule.h"

IMPLEMENT_MODULE(ExtendedLibraryModule, ExtendedLibrary);


#define LOCTEXT_NAMESPACE "ExtendedLibrary"

ExtendedLibraryModule::ExtendedLibraryModule()
{
}

void ExtendedLibraryModule::StartupModule()
{
// Startup LOG MSG
	//UE_LOG(ModuleLog, Warning, TEXT("ExtendedLibrary: Log Started"));
}

void ExtendedLibraryModule::ShutdownModule()
{
// Shutdown LOG MSG
	//UE_LOG(ModuleLog, Warning, TEXT("ExtendedLibrary: Log Ended"));
}