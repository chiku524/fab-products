// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

class FWorldBuilderAuditConvertEditorStyle
{
public:
	static void Register();
	static void Unregister();
	static const FName& GetStyleSetName();
	static const FName TabIconName;
	static const FName TabIconSmallName;
};
