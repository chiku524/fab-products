// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorldBuilderTemplateDefaults.h"

namespace WorldBuilderTemplateDefaults
{
	FWorldBuilderOutdoorParams MakeOutdoorShipped()
	{
		FWorldBuilderOutdoorParams P;
		P.Sky = FWorldBuilderSkyPostParams();
		P.bUseFixedTreePositions = true;
		P.TreeCount = 8;
		return P;
	}

	FWorldBuilderIndoorParams MakeIndoorShipped()
	{
		FWorldBuilderIndoorParams P;
		P.Sky.SunPitchDegrees = -72.f;
		P.Sky.SunYawDegrees = 15.f;
		P.Sky.DirectionalIntensity = 2.2f;
		P.Sky.SunTemperature = 4200.f;
		P.Sky.SkyLightIntensity = 0.85f;
		P.Sky.bVolumetricCloud = false;
		P.Sky.PPFilmSlope = 0.88f;
		P.Sky.PPSceneTint = FLinearColor(1.f, 0.97f, 0.92f, 1.f);
		P.Sky.bPPSceneTint = true;
		P.Sky.BloomIntensity = 0.2f;
		P.Sky.VignetteIntensity = -1.f;
		return P;
	}

	FWorldBuilderOceanParams MakeOceanShipped()
	{
		FWorldBuilderOceanParams P;
		P.Sky.SunPitchDegrees = -35.f;
		P.Sky.SunYawDegrees = -40.f;
		P.Sky.DirectionalIntensity = 10.f;
		P.Sky.SunTemperature = 7200.f;
		P.Sky.SkyLightIntensity = 1.8f;
		P.Sky.bVolumetricCloud = true;
		P.Sky.PPFilmSlope = 0.9f;
		P.Sky.PPSceneTint = FLinearColor(0.92f, 0.96f, 1.f, 1.f);
		P.Sky.bPPSceneTint = true;
		P.Sky.BloomIntensity = 0.22f;
		P.Sky.VignetteIntensity = 0.06f;
		return P;
	}

	FWorldBuilderCityParams MakeCityShipped()
	{
		FWorldBuilderCityParams P;
		P.Sky.SunPitchDegrees = -48.f;
		P.Sky.SunYawDegrees = 55.f;
		P.Sky.DirectionalIntensity = 7.5f;
		P.Sky.SunTemperature = 6200.f;
		P.Sky.SkyLightIntensity = 1.45f;
		P.Sky.bVolumetricCloud = true;
		P.Sky.PPFilmSlope = 0.9f;
		P.Sky.PPSceneTint = FLinearColor(0.98f, 0.98f, 1.f, 1.f);
		P.Sky.bPPSceneTint = true;
		P.Sky.BloomIntensity = 0.17f;
		P.Sky.VignetteIntensity = 0.12f;
		return P;
	}
}
