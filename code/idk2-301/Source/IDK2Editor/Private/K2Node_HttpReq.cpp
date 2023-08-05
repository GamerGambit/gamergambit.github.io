// Copyright (c) Tyler Duffus

#include "K2Node_HttpReq.h"
#include "HttpReqProxy.h"

UK2Node_HttpReq::UK2Node_HttpReq(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ProxyFactoryFunctionName = GET_FUNCTION_NAME_CHECKED(UHttpReqProxy, CreateProxyObjectForHTTPRequest);
	ProxyFactoryClass = UHttpReqProxy::StaticClass();
	ProxyClass = UHttpReqProxy::StaticClass();
}
