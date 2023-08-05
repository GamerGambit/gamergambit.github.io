// Copyright (c) Tyler Duffus

#pragma once

#include "UObject/Object.h"

#include "HttpReqProxy.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSimpleMCDelegate);

UCLASS(MinimalAPI)
class UHttpReqProxy : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
	FString URL;

	UPROPERTY(BlueprintAssignable)
	FSimpleMCDelegate OnComplete;

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true"))
	static UHttpReqProxy* CreateProxyObjectForHTTPRequest(FString InURL);
};
