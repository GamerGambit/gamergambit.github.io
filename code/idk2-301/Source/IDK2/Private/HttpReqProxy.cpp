// Copyright (c) Tyler Duffus

#include "HttpReqProxy.h"

#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"

UHttpReqProxy* UHttpReqProxy::CreateProxyObjectForHTTPRequest(FString InURL)
{
	auto* proxy = NewObject<ThisClass>();
	proxy->SetFlags(RF_StrongRefOnFrame);
	proxy->URL = InURL;

	FHttpRequestRef req = FHttpModule::Get().CreateRequest();
	req->SetURL(InURL);
	req->SetVerb("GET");
	req->OnProcessRequestComplete().BindLambda([proxy](FHttpRequestPtr InRequest, FHttpResponsePtr InResponse, bool InConnectedSuccessfully)
	{
			if (InResponse->GetResponseCode() < 400 && InConnectedSuccessfully)
			{
				proxy->OnComplete.Broadcast();
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("HTTP GET (%s) failed with code %d"), *proxy->URL, InResponse->GetResponseCode());
			}
	});
	req->ProcessRequest();

	return proxy;
}
