// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorldBuilderTemplatesSettings.h"

UWorldBuilderTemplatesSettings::UWorldBuilderTemplatesSettings()
{
	CategoryName = TEXT("Plugins");
	SectionName = TEXT("World Builder Templates");

	ExtraPackagePathRoots.Add(TEXT("/Engine/Maps/Templates"));
}

FName UWorldBuilderTemplatesSettings::GetCategoryName() const
{
	return FName(TEXT("Plugins"));
}

FName UWorldBuilderTemplatesSettings::GetSectionName() const
{
	return FName(TEXT("World Builder Templates"));
}
