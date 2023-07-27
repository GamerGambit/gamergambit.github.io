// Copyright (c) Tyler Duffus

#include "PrintBPFL.h"

#define CALL_UE_LOG(Verbosity) UE_LOG(LogBlueprintUserMessages, Verbosity, TEXT("%s"), *InString)
void UPrintBPFL::PrintWithVerbosity(const FString& InString, EPrintLogVerbosity InVerbosity, bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration, FName Key)
{
	if (bPrintToLog)
	{
		switch (InVerbosity)
		{
		case EPrintLogVerbosity::Fatal:
			CALL_UE_LOG(Fatal);
			break;

		case EPrintLogVerbosity::Error:
			CALL_UE_LOG(Error);
			break;

		case EPrintLogVerbosity::Warning:
			CALL_UE_LOG(Warning);
			break;

		case EPrintLogVerbosity::Display:
			CALL_UE_LOG(Display);
			break;

		case EPrintLogVerbosity::Log:
			CALL_UE_LOG(Log);
			break;

		case EPrintLogVerbosity::Verbose:
			CALL_UE_LOG(Verbose);
			break;

		case EPrintLogVerbosity::VeryVerbose:
			CALL_UE_LOG(VeryVerbose);
			break;

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
