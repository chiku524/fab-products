// Copyright (c) [PUBLISHER_NAME]. All Rights Reserved.

#pragma once

#include "Modules/ModuleInterface.h"

class FWorldBuilderAuditConvertEditorModule : public IModuleInterface
{
public:
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
