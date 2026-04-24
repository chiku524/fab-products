// Copyright (c) Immersive Labs. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "WorldBuilderTemplateTypes.generated.h"

/** Which procedural layout the recipe builds. */
UENUM(BlueprintType)
enum class EWorldBuilderTemplateKind : uint8
{
	Outdoor UMETA(DisplayName = "Outdoor"),
	IndoorBlockout UMETA(DisplayName = "Indoor blockout"),
	Ocean UMETA(DisplayName = "Ocean / coast"),
	City UMETA(DisplayName = "City / plaza"),
};

/** Tunable sky / post stack (shared building block for templates). */
USTRUCT(BlueprintType)
struct FWorldBuilderSkyPostParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	float SunPitchDegrees = -42.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	float SunYawDegrees = 48.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	float DirectionalIntensity = 9.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	float SunTemperature = 5800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	float SkyLightIntensity = 1.65f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	bool bVolumetricCloud = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post")
	float PPFilmSlope = 0.92f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post")
	FLinearColor PPSceneTint = FLinearColor(1.f, 0.99f, 0.96f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post")
	bool bPPSceneTint = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post")
	float BloomIntensity = 0.24f;

	/** Negative = do not override vignette on the post process volume. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Post")
	float VignetteIntensity = -1.f;
};

USTRUCT(BlueprintType)
struct FWorldBuilderOutdoorParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	FWorldBuilderSkyPostParams Sky;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reflection")
	FVector ReflectionCaptureLocation = FVector(200.f, -120.f, 220.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reflection")
	float ReflectionCaptureRadius = 5200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float FogDensity = 0.005f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	FLinearColor FogInscatteringColor = FLinearColor(0.72f, 0.78f, 0.88f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ground")
	FVector GroundPlaneScale = FVector(24.f, 24.f, 1.f);

	/** When true, uses the original shipped tree anchor points (deterministic). When false, trees are scattered with the random stream. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trees")
	bool bUseFixedTreePositions = true;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trees", meta = (ClampMin = "1", ClampMax = "64"))
	int32 TreeCount = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trees", meta = (EditCondition = "!bUseFixedTreePositions"))
	float TreeSpawnHalfExtentXY = 1350.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trees")
	float TreeVisualScale = 1.2f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	int32 PathStoneCount = 17;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	float PathStartX = -880.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	float PathY = 70.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Path")
	float PathStep = 110.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rocks")
	int32 RockClusterCount = 8;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rocks")
	float RockScatterHalfExtentXY = 1350.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Rocks")
	float RockClusterSpread = 200.f;
};

USTRUCT(BlueprintType)
struct FWorldBuilderIndoorParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	FWorldBuilderSkyPostParams Sky;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reflection")
	FVector ReflectionCaptureLocation = FVector(0.f, 0.f, 220.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reflection")
	float ReflectionCaptureRadius = 3800.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor")
	FVector FloorPlaneScale = FVector(12.5f, 12.5f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Floor")
	float FloorZ = -20.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stairs")
	int32 StairTreadCount = 6;
};

USTRUCT(BlueprintType)
struct FWorldBuilderOceanParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	FWorldBuilderSkyPostParams Sky;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reflection")
	FVector ReflectionCaptureLocation = FVector(-280.f, 140.f, 120.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reflection")
	float ReflectionCaptureRadius = 7500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
	FVector WaterPlaneScale = FVector(42.f, 42.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Water")
	float WaterZ = -5.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float FogDensity = 0.024f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	FLinearColor FogInscatteringColor = FLinearColor(0.12f, 0.32f, 0.52f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float VolumetricFogDistance = 9500.f;
};

USTRUCT(BlueprintType)
struct FWorldBuilderCityParams
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sky")
	FWorldBuilderSkyPostParams Sky;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reflection")
	FVector ReflectionCaptureLocation = FVector(0.f, 0.f, 180.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Reflection")
	float ReflectionCaptureRadius = 4200.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Streets")
	FVector StreetPlaneScale = FVector(28.f, 28.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Streets")
	FVector PlazaPlaneScale = FVector(14.f, 14.f, 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Streets")
	float PlazaZ = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	float FogDensity = 0.01f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Fog")
	FLinearColor FogInscatteringColor = FLinearColor(0.55f, 0.58f, 0.62f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid", meta = (ClampMin = "3", ClampMax = "21"))
	int32 TowerGridSize = 9;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float TowerGridStep = 480.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float TowerHeightBase = 130.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Grid")
	float TowerHeightVariation = 420.f;
};
