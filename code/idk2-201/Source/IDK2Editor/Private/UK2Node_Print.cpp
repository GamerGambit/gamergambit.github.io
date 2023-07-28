// Copyright (c) Tyler Duffus

#include "K2Node_Print.h"
#include "PrintBPFL.h"

#include "BlueprintActionDatabaseRegistrar.h"
#include "BlueprintNodeSpawner.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"

#define MOVEPINS_SameName(Name, DestNode) { \
	auto* srcPin = FindPinChecked(Name); \
	auto* dstPin = DestNode->FindPinChecked(Name); \
	auto response = CompilerContext.MovePinLinksToIntermediate(*srcPin, *dstPin); \
	if (!ensureMsgf(response.CanSafeConnect(), TEXT("%s"), *response.Message.ToString())) \
		CompilerContext.MessageLog.Error(*FString::Printf(TEXT("@@: {0}"), *response.Message.ToString()), this); \
}

void UK2Node_Print::AllocateDefaultPins()
{
	SetEnabledState(ENodeEnabledState::DevelopmentOnly);
	AdvancedPinDisplay = ENodeAdvancedPins::Hidden;

	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Execute);
	CreatePin(EGPD_Output, UEdGraphSchema_K2::PC_Exec, UEdGraphSchema_K2::PN_Then);

	CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_String, "InString")->DefaultValue = TEXT("Hello");

	{
		auto* pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Byte, StaticEnum<EPrintLogVerbosity>(), "InVerbosity");
		pin->DefaultValue = StaticEnum<EPrintLogVerbosity>()->GetNameStringByIndex(3); // Default to `Display`
		pin->bAdvancedView = true;
	}
	{
		auto* pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Boolean, "bPrintToScreen");
		pin->DefaultValue = LexToString(true);
		pin->bAdvancedView = true;
	}

	{
		auto* pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Boolean, "bPrintToLog");
		pin->DefaultValue = LexToString(true);
		pin->bAdvancedView = true;
	}

	{
		auto* pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Struct, TBaseStructure<FLinearColor>::Get(), "TextColor");
		pin->DefaultValue = FLinearColor::Blue.ToString();
		pin->bAdvancedView = true;
	}

	{
		auto* pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Real, "Duration");
		pin->DefaultValue = LexToString(2.0f);
		pin->bAdvancedView = true;
	}

	{
		auto* pin = CreatePin(EGPD_Input, UEdGraphSchema_K2::PC_Name, "Key");
		pin->DefaultValue = LexToString(NAME_None);
		pin->bAdvancedView = true;
	}
}

void UK2Node_Print::ExpandNode(FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph)
{
	Super::ExpandNode(CompilerContext, SourceGraph);

	auto* FuncCallNode = CompilerContext.SpawnIntermediateNode<UK2Node_CallFunction>(this, SourceGraph);
	const FName CommandFuncName = GET_FUNCTION_NAME_CHECKED(UPrintBPFL, PrintWithVerbosity);
	FuncCallNode->FunctionReference.SetExternalMember(CommandFuncName, UPrintBPFL::StaticClass());
	FuncCallNode->AllocateDefaultPins();

	MOVEPINS_SameName(UEdGraphSchema_K2::PN_Execute, FuncCallNode);
	MOVEPINS_SameName(UEdGraphSchema_K2::PN_Then, FuncCallNode);
	MOVEPINS_SameName(FName("InString"), FuncCallNode);
	MOVEPINS_SameName(FName("InVerbosity"), FuncCallNode);
	MOVEPINS_SameName(FName("bPrintToScreen"), FuncCallNode);
	MOVEPINS_SameName(FName("bPrintToLog"), FuncCallNode);
	MOVEPINS_SameName(FName("TextColor"), FuncCallNode);
	MOVEPINS_SameName(FName("Duration"), FuncCallNode);
	MOVEPINS_SameName(FName("Key"), FuncCallNode);

	BreakAllNodeLinks();
}

void UK2Node_Print::GetMenuActions(class FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	UClass* ActionKey = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}
