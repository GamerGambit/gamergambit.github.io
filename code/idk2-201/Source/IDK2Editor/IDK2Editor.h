// Copyright (c) Tyler Duffus
#pragma once

#include "Modules/ModuleManager.h"

class FIDK2Editor : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
