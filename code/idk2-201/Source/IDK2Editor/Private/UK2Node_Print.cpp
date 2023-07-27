// Copyright (c) Tyler Duffus

#include "K2Node_Print.h"
#include "PrintBPFL.h"

#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "K2Node_CallFunction.h"
#include "KismetCompiler.h"

#define MOVEPINS_SameName(Name, DestNode) { \
	auto* srcPin = FindPinChecked(Name); \
	auto* dstPin = DestNode->FindPinChecked(Name); \
	auto response = CompilerContext.MovePinLinksToIntermediate(*srcPin, *dstPin); \
	if (!ensureMsgf(response.CanSafeConnect(), TEXT("%s"), *response.Message.ToString())) \
		CompilerContext.MessageLog.Error(*FText::Format(NSLOCTEXT("UK2Node_Print", "InternalConnectionError", "@@: {0}"), response.Message).ToString(), this); \
}

void UK2Node_Print::AllocateDefaultPins()
{
	SetEnabledState(ENodeEnabledState::DevelopmentOnly, false);
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
	// actions get registered under specific object-keys; the idea is that 
	// actions might have to be updated (or deleted) if their object-key is  
	// mutated (or removed)... here we use the node's class (so if the node 
	// type disappears, then the action should go with it)
	UClass* ActionKey = GetClass();
	// to keep from needlessly instantiating a UBlueprintNodeSpawner, first   
	// check to make sure that the registrar is looking for actions of this type
	// (could be regenerating actions for a specific asset, and therefore the 
	// registrar would only accept actions corresponding to that asset)
	if (ActionRegistrar.IsOpenForRegistration(ActionKey))
	{
		UBlueprintNodeSpawner* NodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(NodeSpawner != nullptr);

		ActionRegistrar.AddBlueprintAction(ActionKey, NodeSpawner);
	}
}
