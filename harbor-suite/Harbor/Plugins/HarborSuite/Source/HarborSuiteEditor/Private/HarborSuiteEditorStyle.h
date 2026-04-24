// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"

/**
 * Slate style: loads Resources/Icon128.png for Window menu / tab spawner icons.
 */
class FHarborSuiteEditorStyle
{
public:
	static void Register();
	static void Unregister();

	static const FName& GetStyleSetName();

	static const FVector2D Icon16;

	static const FName TabIconName;
	static const FName TabIconSmallName;
};
