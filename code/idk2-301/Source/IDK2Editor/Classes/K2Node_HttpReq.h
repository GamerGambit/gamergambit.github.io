// Copyright (c) Tyler Duffus

#pragma once

#include "K2Node_BaseAsyncTask.h"

#include "K2Node_HttpReq.generated.h"

UCLASS()
class UK2Node_HttpReq : public UK2Node_BaseAsyncTask
{
	GENERATED_BODY()

public:
	UK2Node_HttpReq(const FObjectInitializer& ObjectInitializer);
};
