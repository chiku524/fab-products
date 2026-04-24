// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "Styling/SlateTypes.h"

class FWorkflowToolkitEditorStyle
{
public:
	static void Register();
	static void Unregister();

	static const FName& GetStyleSetName();

	static const FSlateBrush* GetBrush(FName BrushName);

	static const FName TabIconName;
	static const FName TabIconSmallName;

	/** Theme-aware panel chrome (rounded, follows editor Background / Recessed). */
	static const FName PageBackgroundBrushName;
	/** Elevated cards (actions, grids). */
	static const FName CardSurfaceBrushName;
	/** Intro / hero strip at top. */
	static const FName HeroCardBrushName;
	/** Console command block (recessed input feel). */
	static const FName ConsoleCardBrushName;
	/** Secondary info (e.g. runtime hint). */
	static const FName InfoCardBrushName;

private:
	FWorkflowToolkitEditorStyle() = delete;
};
