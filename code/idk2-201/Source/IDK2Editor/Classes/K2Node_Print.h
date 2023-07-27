// Copyright (c) Tyler Duffus

#pragma once

#include "K2Node.h"

#include "K2Node_Print.generated.h"

UCLASS()
class UK2Node_Print : public UK2Node
{
	GENERATED_BODY()

public:
#pragma region UEdGraphNode
	virtual void AllocateDefaultPins() override;
	virtual FLinearColor GetNodeTitleColor() const override { return FLinearColor(1.0f, 0.1f, 1.0f); }
	virtual FText GetNodeTitle(ENodeTitleType::Type TitleType) const override { return FText::FromString("Print with Verbosity"); }
	virtual void ExpandNode(class FKismetCompilerContext& CompilerContext, UEdGraph* SourceGraph) override;
#pragma endregion // UEdGraphNode

#pragma region UK2Node
	virtual void GetMenuActions(class FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
#pragma endregion // UK2Node
};
