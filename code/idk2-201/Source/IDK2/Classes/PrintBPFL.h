// Copyright (c) Tyler Duffus

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "PrintBPFL.generated.h"

UENUM()
enum class EPrintLogVerbosity : uint8
{
	Fatal,
	Error,
	Warning,
	Display,
	Log,
	Verbose,
	VeryVerbose
};

UCLASS()
class IDK2_API UPrintBPFL : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static void PrintWithVerbosity(const FString& InString, EPrintLogVerbosity InVerbosity, bool bPrintToScreen, bool bPrintToLog, FLinearColor TextColor, float Duration, FName Key);
};
