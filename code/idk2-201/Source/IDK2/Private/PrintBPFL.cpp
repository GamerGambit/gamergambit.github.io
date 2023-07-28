// Copyright (c) Tyler Duffus

#include "PrintBPFL.h"

#define ADD_VERBOSITY_CASE(Verbosity) case EPrintLogVerbosity::Verbosity: UE_LOG(LogBlueprintUserMessages, Verbosity, TEXT("%s"), *InString); break;
void UPrintBPFL::PrintWithVerbosity(const FString& InString, EPrintLogVerbosity InVerbosity, bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration, FName Key)
{
	if (bPrintToLog)
	{
		switch (InVerbosity)
		{
			ADD_VERBOSITY_CASE(Fatal);
			ADD_VERBOSITY_CASE(Error);
			ADD_VERBOSITY_CASE(Warning);
			ADD_VERBOSITY_CASE(Display);
			ADD_VERBOSITY_CASE(Log);
			ADD_VERBOSITY_CASE(Verbose);
			ADD_VERBOSITY_CASE(VeryVerbose);

		default:
			checkNoEntry();
			break;
		}
	}

	if (bPrintToLog)
	{
		uint64 InnerKey = (Key != NAME_None) ? GetTypeHash(Key) : - 1;
		GEngine->AddOnScreenDebugMessage(InnerKey, Duration, TextColor.ToFColor(true), InString);
	}
}
#undef ADD_VERBOSITY_CASE
