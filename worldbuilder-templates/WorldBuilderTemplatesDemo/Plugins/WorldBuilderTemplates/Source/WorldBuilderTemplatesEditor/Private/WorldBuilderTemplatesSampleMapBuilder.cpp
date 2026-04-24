// Copyright (c) Immersive Labs. All Rights Reserved.

#include "WorldBuilderTemplatesSampleMapBuilder.h"

#include "Components/DirectionalLightComponent.h"
#include "Components/ExponentialHeightFogComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/RectLightComponent.h"
#include "Components/SkyAtmosphereComponent.h"
#include "Components/SkyLightComponent.h"
#include "Components/SphereReflectionCaptureComponent.h"
#include "Components/SpotLightComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/VolumetricCloudComponent.h"
#include "Engine/DirectionalLight.h"
#include "Engine/ExponentialHeightFog.h"
#include "Engine/PointLight.h"
#include "Engine/PostProcessVolume.h"
#include "Engine/RectLight.h"
#include "Engine/SkyLight.h"
#include "Engine/SphereReflectionCapture.h"
#include "Engine/SpotLight.h"
#include "Engine/StaticMeshActor.h"
#include "Engine/World.h"
#include "Materials/MaterialInterface.h"
#include "Math/RandomStream.h"
#include "WorldBuilderTemplateDefaults.h"
#include "WorldBuilderTemplateRecipe.h"

namespace
{
	FActorSpawnParameters MakeSpawnParams()
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		return Params;
	}

	UStaticMesh* LoadShapeMesh(const TCHAR* ObjectPath)
	{
		return LoadObject<UStaticMesh>(nullptr, ObjectPath);
	}

	UMaterialInterface* TryLoadMaterial(const TCHAR* ObjectPath)
	{
		return LoadObject<UMaterialInterface>(nullptr, ObjectPath);
	}

	UMaterialInterface* ResolveGroundMaterial()
	{
		static const TCHAR* const Paths[] = {
			TEXT("/Engine/EngineMaterials/WorldGridMaterial.WorldGridMaterial"),
			TEXT("/Engine/TemplateResources/M_PrototypeGrid.M_PrototypeGrid"),
		};
		for (const TCHAR* Path : Paths)
		{
			if (UMaterialInterface* M = TryLoadMaterial(Path))
			{
				return M;
			}
		}
		return nullptr;
	}

	UMaterialInterface* ResolveNeutralMaterial()
	{
		static const TCHAR* const Paths[] = {
			TEXT("/Engine/EngineMaterials/DefaultMaterial.DefaultMaterial"),
			TEXT("/Engine/EngineMaterials/DefaultDiffuse.DefaultDiffuse"),
		};
		for (const TCHAR* Path : Paths)
		{
			if (UMaterialInterface* M = TryLoadMaterial(Path))
			{
				return M;
			}
		}
		return nullptr;
	}

	AStaticMeshActor* SpawnShape(
		UWorld* World,
		UStaticMesh* Mesh,
		const FVector& Location,
		const FRotator& Rotation,
		const FVector& Scale,
		const TCHAR* Label,
		UMaterialInterface* Material = nullptr)
	{
		if (!World || !Mesh)
		{
			return nullptr;
		}

		AStaticMeshActor* Actor = World->SpawnActor<AStaticMeshActor>(Location, Rotation, MakeSpawnParams());
		if (!Actor)
		{
			return nullptr;
		}

		Actor->SetActorLabel(Label);
		Actor->SetActorScale3D(Scale);
		if (UStaticMeshComponent* SMC = Actor->GetStaticMeshComponent())
		{
			SMC->SetStaticMesh(Mesh);
			SMC->SetMobility(EComponentMobility::Movable);
			if (Material)
			{
				SMC->SetMaterial(0, Material);
			}
		}

		return Actor;
	}

	void SpawnSpotToward(
		UWorld* World,
		const FVector& LightLocation,
		const FVector& Target,
		float Intensity,
		float OuterDegrees,
		float Temperature,
		const TCHAR* Label);

	void AddVolumetricCloud(UWorld* World)
	{
		if (!World)
		{
			return;
		}
		if (AVolumetricCloud* Cloud = World->SpawnActor<AVolumetricCloud>(FVector::ZeroVector, FRotator::ZeroRotator, MakeSpawnParams()))
		{
			Cloud->SetActorLabel(TEXT("VolumetricCloud"));
		}
	}

	void AddUnboundPostProcess(
		UWorld* World,
		const TCHAR* Label,
		float FilmSlope,
		const FLinearColor& SceneColorTint,
		bool bTintScene,
		float BloomIntensity,
		float VignetteIntensity)
	{
		if (!World)
		{
			return;
		}
		APostProcessVolume* Vol = World->SpawnActor<APostProcessVolume>(FVector::ZeroVector, FRotator::ZeroRotator, MakeSpawnParams());
		if (!Vol)
		{
			return;
		}
		Vol->SetActorLabel(Label);
		Vol->bUnbound = true;
		Vol->BlendWeight = 1.f;
		Vol->Priority = 0.f;
		FPostProcessSettings& S = Vol->Settings;
		S.bOverride_FilmSlope = true;
		S.FilmSlope = FilmSlope;
		if (bTintScene)
		{
			S.bOverride_SceneColorTint = true;
			S.SceneColorTint = SceneColorTint;
		}
		if (BloomIntensity >= 0.f)
		{
			S.bOverride_BloomIntensity = true;
			S.BloomIntensity = BloomIntensity;
		}
		if (VignetteIntensity >= 0.f)
		{
			S.bOverride_VignetteIntensity = true;
			S.VignetteIntensity = VignetteIntensity;
		}
	}

	void AddSkySunCloudsAndPost(
		UWorld* World,
		float SunPitchDegrees,
		float SunYawDegrees,
		float DirectionalIntensity,
		float SunTemperature,
		float SkyLightIntensity,
		bool bVolumetricCloud,
		float PPFilmSlope,
		const FLinearColor& PPSceneTint,
		bool bPPSceneTint,
		float BloomIntensity,
		float VignetteIntensity)
	{
		if (!World)
		{
			return;
		}

		const FActorSpawnParameters Params = MakeSpawnParams();

		if (ADirectionalLight* Sun = World->SpawnActor<ADirectionalLight>(FVector::ZeroVector, FRotator(SunPitchDegrees, SunYawDegrees, 0.f), Params))
		{
			Sun->SetActorLabel(TEXT("DirectionalLight"));
			if (UDirectionalLightComponent* DLC = Cast<UDirectionalLightComponent>(Sun->GetLightComponent()))
			{
				DLC->SetIntensity(DirectionalIntensity);
				DLC->SetUseTemperature(true);
				DLC->SetTemperature(SunTemperature);
				DLC->SetLightSourceAngle(0.55f);
			}
		}

		if (ASkyLight* Sky = World->SpawnActor<ASkyLight>(FVector::ZeroVector, FRotator::ZeroRotator, Params))
		{
			Sky->SetActorLabel(TEXT("SkyLight"));
			if (USkyLightComponent* SLC = Cast<USkyLightComponent>(Sky->GetLightComponent()))
			{
				SLC->SetIntensity(SkyLightIntensity);
				SLC->bRealTimeCapture = true;
			}
		}

		if (ASkyAtmosphere* Atmo = World->SpawnActor<ASkyAtmosphere>(FVector::ZeroVector, FRotator::ZeroRotator, Params))
		{
			Atmo->SetActorLabel(TEXT("SkyAtmosphere"));
		}

		if (bVolumetricCloud)
		{
			AddVolumetricCloud(World);
		}

		AddUnboundPostProcess(World, TEXT("PostProcess_Global"), PPFilmSlope, PPSceneTint, bPPSceneTint, BloomIntensity, VignetteIntensity);
	}

	void AddSphereReflectionCapture(UWorld* World, const FVector& Location, float InfluenceRadius, const TCHAR* Label)
	{
		if (!World)
		{
			return;
		}
		if (ASphereReflectionCapture* Cap = World->SpawnActor<ASphereReflectionCapture>(Location, FRotator::ZeroRotator, MakeSpawnParams()))
		{
			Cap->SetActorLabel(Label);
			if (USphereReflectionCaptureComponent* Sph = Cast<USphereReflectionCaptureComponent>(Cap->GetCaptureComponent()))
			{
				Sph->InfluenceRadius = InfluenceRadius;
			}
		}
	}

	void SpawnRectLightFacingDown(
		UWorld* World,
		const FVector& Location,
		float SourceWidth,
		float SourceHeight,
		float Intensity,
		float Temperature,
		const TCHAR* Label)
	{
		if (!World)
		{
			return;
		}
		if (ARectLight* RL = World->SpawnActor<ARectLight>(Location, FRotator(-90.f, 0.f, 0.f), MakeSpawnParams()))
		{
			RL->SetActorLabel(Label);
			if (URectLightComponent* RC = RL->RectLightComponent.Get())
			{
				RC->SetSourceWidth(SourceWidth);
				RC->SetSourceHeight(SourceHeight);
				RC->SetIntensity(Intensity);
				RC->SetUseTemperature(true);
				RC->SetTemperature(Temperature);
				RC->SetAttenuationRadius(2500.f);
				RC->SetMobility(EComponentMobility::Movable);
			}
		}
	}

	void SpawnStreetLamp(
		UWorld* World,
		UStaticMesh* Cube,
		UMaterialInterface* Mat,
		const FVector& StreetBase,
		const TCHAR* LabelPrefix)
	{
		if (!World || !Cube)
		{
			return;
		}
		TCHAR Buf[72];
		FCString::Snprintf(Buf, UE_ARRAY_COUNT(Buf), TEXT("%s_Pole"), LabelPrefix);
		(void)SpawnShape(
			World,
			Cube,
			StreetBase + FVector(0.f, 0.f, 195.f),
			FRotator::ZeroRotator,
			FVector(0.11f, 0.11f, 3.6f),
			Buf,
			Mat);
		FCString::Snprintf(Buf, UE_ARRAY_COUNT(Buf), TEXT("%s_Lamp"), LabelPrefix);
		SpawnSpotToward(
			World,
			StreetBase + FVector(0.f, 0.f, 395.f),
			StreetBase + FVector(0.f, 0.f, 8.f),
			22000.f,
			48.f,
			4800.f,
			Buf);
	}

	void SpawnPointFill(
		UWorld* World,
		const FVector& Location,
		float Intensity,
		float AttenuationRadius,
		float Temperature,
		const TCHAR* Label)
	{
		if (!World)
		{
			return;
		}
		if (APointLight* PL = World->SpawnActor<APointLight>(Location, FRotator::ZeroRotator, MakeSpawnParams()))
		{
			PL->SetActorLabel(Label);
			if (UPointLightComponent* PC = PL->PointLightComponent.Get())
			{
				PC->SetIntensity(Intensity);
				PC->SetAttenuationRadius(AttenuationRadius);
				PC->SetUseTemperature(true);
				PC->SetTemperature(Temperature);
				PC->SetMobility(EComponentMobility::Movable);
			}
		}
	}

	void SpawnSpotToward(
		UWorld* World,
		const FVector& LightLocation,
		const FVector& Target,
		float Intensity,
		float OuterDegrees,
		float Temperature,
		const TCHAR* Label)
	{
		if (!World)
		{
			return;
		}
		const FVector Dir = (Target - LightLocation).GetSafeNormal();
		const FRotator Face = Dir.Rotation();
		if (ASpotLight* SL = World->SpawnActor<ASpotLight>(LightLocation, Face, MakeSpawnParams()))
		{
			SL->SetActorLabel(Label);
			if (USpotLightComponent* SC = SL->SpotLightComponent.Get())
			{
				SC->SetIntensity(Intensity);
				SC->SetOuterConeAngle(OuterDegrees);
				SC->SetUseTemperature(true);
				SC->SetTemperature(Temperature);
				SC->SetMobility(EComponentMobility::Movable);
			}
		}
	}

	void SpawnStylizedTree(
		UWorld* World,
		UStaticMesh* Cylinder,
		UStaticMesh* Cone,
		UMaterialInterface* TrunkMat,
		UMaterialInterface* CanopyMat,
		const FVector& Base,
		int32 Index,
		UMaterialInterface* FallbackMat,
		float VisualScale = 1.f)
	{
		if (!World || !Cylinder || !Cone)
		{
			return;
		}
		const float VS = FMath::Clamp(VisualScale, 0.5f, 3.f);
		TCHAR LabelBuf[64];
		FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Tree_%d_Trunk"), Index);
		(void)SpawnShape(
			World,
			Cylinder,
			Base + FVector(0.f, 0.f, 150.f * VS),
			FRotator::ZeroRotator,
			FVector(0.26f * VS, 0.26f * VS, 1.65f * VS),
			LabelBuf,
			TrunkMat ? TrunkMat : FallbackMat);
		FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Tree_%d_Canopy"), Index);
		(void)SpawnShape(
			World,
			Cone,
			Base + FVector(0.f, 0.f, 395.f * VS),
			FRotator(0.f, 0.f, 0.f),
			FVector(1.35f * VS, 1.35f * VS, 1.55f * VS),
			LabelBuf,
			CanopyMat ? CanopyMat : FallbackMat);
	}

	void SpawnRockCluster(UWorld* World, UStaticMesh* Sphere, UMaterialInterface* Mat, const FVector& Base, int32 ClusterIndex, FRandomStream& Rand, float Spread = 120.f)
	{
		if (!World || !Sphere)
		{
			return;
		}
		const int32 Num = 3 + (Rand.GetFraction() > 0.45f ? 1 : 0);
		for (int32 i = 0; i < Num; ++i)
		{
			const float ox = Rand.FRandRange(-Spread, Spread);
			const float oy = Rand.FRandRange(-Spread, Spread);
			const float s = Rand.FRandRange(0.4f, 1.f);
			TCHAR LabelBuf[64];
			FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Rock_%d_%d"), ClusterIndex, i);
			(void)SpawnShape(
				World,
				Sphere,
				Base + FVector(ox, oy, 55.f * s),
				FRotator(Rand.FRandRange(-8.f, 8.f), Rand.FRandRange(0.f, 360.f), Rand.FRandRange(-8.f, 8.f)),
				FVector(s, s * Rand.FRandRange(0.85f, 1.15f), s * 0.75f),
				LabelBuf,
				Mat);
		}
	}

	void AddSkyFromParams(UWorld* World, const FWorldBuilderSkyPostParams& Sky)
	{
		AddSkySunCloudsAndPost(
			World,
			Sky.SunPitchDegrees,
			Sky.SunYawDegrees,
			Sky.DirectionalIntensity,
			Sky.SunTemperature,
			Sky.SkyLightIntensity,
			Sky.bVolumetricCloud,
			Sky.PPFilmSlope,
			Sky.PPSceneTint,
			Sky.bPPSceneTint,
			Sky.BloomIntensity,
			Sky.VignetteIntensity);
	}
}


void WorldBuilderTemplatesSampleMapBuilder::SetupOutdoor(UWorld* World)
{
	if (!World)
	{
		return;
	}
	const FWorldBuilderOutdoorParams P = WorldBuilderTemplateDefaults::MakeOutdoorShipped();
	FRandomStream Rand(91021);
	SetupOutdoor(World, P, Rand);
}

void WorldBuilderTemplatesSampleMapBuilder::SetupOutdoor(UWorld* World, const FWorldBuilderOutdoorParams& Params, FRandomStream& Rand)
{
	if (!World)
	{
		return;
	}

	UStaticMesh* Plane = LoadShapeMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
	UStaticMesh* Cube = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	UStaticMesh* Cylinder = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cylinder.Cylinder"));
	UStaticMesh* Cone = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cone.Cone"));
	UStaticMesh* Sphere = LoadShapeMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	UMaterialInterface* GroundMat = ResolveGroundMaterial();
	UMaterialInterface* NeutralMat = ResolveNeutralMaterial();

	AddSkyFromParams(World, Params.Sky);

	AddSphereReflectionCapture(World, Params.ReflectionCaptureLocation, Params.ReflectionCaptureRadius, TEXT("ReflectionCapture_Main"));

	const FActorSpawnParameters FogParamsOutdoor = MakeSpawnParams();
	if (AExponentialHeightFog* Mist = World->SpawnActor<AExponentialHeightFog>(FVector::ZeroVector, FRotator::ZeroRotator, FogParamsOutdoor))
	{
		Mist->SetActorLabel(TEXT("GroundMist"));
		if (UExponentialHeightFogComponent* Fc = Mist->GetComponent())
		{
			Fc->SetFogDensity(Params.FogDensity);
			Fc->SetFogInscatteringColor(Params.FogInscatteringColor);
		}
	}

	if (Plane)
	{
		AStaticMeshActor* Ground = SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, 0.f),
			FRotator::ZeroRotator,
			Params.GroundPlaneScale,
			TEXT("GroundPlane"),
			GroundMat ? GroundMat : NeutralMat);
		(void)Ground;
	}

	static const FVector FixedTreeBases[] = {
		FVector(-720.f, 460.f, 0.f),
		FVector(640.f, -500.f, 0.f),
		FVector(-280.f, -840.f, 0.f),
		FVector(860.f, 620.f, 0.f),
		FVector(-980.f, -240.f, 0.f),
		FVector(180.f, 900.f, 0.f),
		FVector(-560.f, -780.f, 0.f),
		FVector(920.f, -120.f, 0.f),
	};
	static const int32 NumFixedTreeBases = UE_ARRAY_COUNT(FixedTreeBases);

	if (Params.bUseFixedTreePositions)
	{
		const int32 N = FMath::Clamp(Params.TreeCount, 1, NumFixedTreeBases);
		for (int32 i = 0; i < N; ++i)
		{
			SpawnStylizedTree(World, Cylinder, Cone, NeutralMat, NeutralMat, FixedTreeBases[i], i, NeutralMat, Params.TreeVisualScale);
		}
	}
	else
	{
		const int32 N = FMath::Max(0, Params.TreeCount);
		for (int32 i = 0; i < N; ++i)
		{
			const float Ox = Rand.FRandRange(-Params.TreeSpawnHalfExtentXY, Params.TreeSpawnHalfExtentXY);
			const float Oy = Rand.FRandRange(-Params.TreeSpawnHalfExtentXY, Params.TreeSpawnHalfExtentXY);
			SpawnStylizedTree(World, Cylinder, Cone, NeutralMat, NeutralMat, FVector(Ox, Oy, 0.f), i, NeutralMat, Params.TreeVisualScale);
		}
	}

	if (Cube)
	{
		const float Mid = (static_cast<float>(FMath::Max(1, Params.PathStoneCount)) - 1.f) * 0.5f;
		for (int32 s = 0; s < Params.PathStoneCount; ++s)
		{
			const float t = static_cast<float>(s) - Mid;
			TCHAR StepLbl[32];
			FCString::Snprintf(StepLbl, UE_ARRAY_COUNT(StepLbl), TEXT("PathStone_%d"), s);
			(void)SpawnShape(
				World,
				Cube,
				FVector(Params.PathStartX + t * Params.PathStep, Params.PathY, 10.f),
				FRotator(0.f, 7.f * t, 0.f),
				FVector(0.5f, 0.42f, 0.14f),
				StepLbl,
				NeutralMat);
		}
		(void)SpawnShape(
			World,
			Cube,
			FVector(820.f, -260.f, 55.f),
			FRotator(0.f, -14.f, 0.f),
			FVector(6.5f, 3.2f, 0.65f),
			TEXT("TerracePad"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cube,
			FVector(-920.f, 520.f, 28.f),
			FRotator(0.f, 22.f, 0.f),
			FVector(5.f, 4.f, 0.45f),
			TEXT("LookoutDeck"),
			NeutralMat);
	}

	for (int32 c = 0; c < Params.RockClusterCount; ++c)
	{
		const float ox = Rand.FRandRange(-Params.RockScatterHalfExtentXY, Params.RockScatterHalfExtentXY);
		const float oy = Rand.FRandRange(-Params.RockScatterHalfExtentXY, Params.RockScatterHalfExtentXY);
		SpawnRockCluster(World, Sphere, NeutralMat, FVector(ox, oy, 0.f), c, Rand, Params.RockClusterSpread);
	}

	SpawnPointFill(World, FVector(-320.f, -200.f, 320.f), 12000.f, 2200.f, 5000.f, TEXT("FillWarm"));
	SpawnPointFill(World, FVector(380.f, 260.f, 260.f), 6500.f, 2000.f, 7500.f, TEXT("FillCool"));
	SpawnPointFill(World, FVector(40.f, -620.f, 180.f), 5500.f, 2800.f, 6200.f, TEXT("FillSide"));
}

void WorldBuilderTemplatesSampleMapBuilder::SetupIndoorBlockout(UWorld* World)
{
	if (!World)
	{
		return;
	}
	const FWorldBuilderIndoorParams P = WorldBuilderTemplateDefaults::MakeIndoorShipped();
	FRandomStream Rand(1);
	SetupIndoorBlockout(World, P, Rand);
}

void WorldBuilderTemplatesSampleMapBuilder::SetupIndoorBlockout(UWorld* World, const FWorldBuilderIndoorParams& Params, FRandomStream& Rand)
{
	(void)Rand;
	if (!World)
	{
		return;
	}

	UStaticMesh* Cube = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	UStaticMesh* Plane = LoadShapeMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));

	UMaterialInterface* GroundMat = ResolveGroundMaterial();
	UMaterialInterface* NeutralMat = ResolveNeutralMaterial();

	AddSkyFromParams(World, Params.Sky);

	AddSphereReflectionCapture(World, Params.ReflectionCaptureLocation, Params.ReflectionCaptureRadius, TEXT("ReflectionCapture_Room"));

	if (Plane)
	{
		(void)SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, Params.FloorZ),
			FRotator::ZeroRotator,
			Params.FloorPlaneScale,
			TEXT("Floor"),
			GroundMat ? GroundMat : NeutralMat);
	}

	if (Cube)
	{
		SpawnShape(World, Cube, FVector(-465.f, 620.f, 233.f), FRotator::ZeroRotator, FVector(7.75f, 0.5f, 4.65f), TEXT("Wall_North_L"), NeutralMat);
		SpawnShape(World, Cube, FVector(465.f, 620.f, 233.f), FRotator::ZeroRotator, FVector(7.75f, 0.5f, 4.65f), TEXT("Wall_North_R"), NeutralMat);
		SpawnShape(World, Cube, FVector(0.f, -620.f, 233.f), FRotator::ZeroRotator, FVector(18.6f, 0.5f, 4.65f), TEXT("Wall_South"), NeutralMat);
		SpawnShape(World, Cube, FVector(620.f, 0.f, 233.f), FRotator(0.f, 90.f, 0.f), FVector(18.6f, 0.5f, 4.65f), TEXT("Wall_East"), NeutralMat);
		SpawnShape(World, Cube, FVector(-620.f, 0.f, 233.f), FRotator(0.f, 90.f, 0.f), FVector(18.6f, 0.5f, 4.65f), TEXT("Wall_West"), NeutralMat);
		SpawnShape(World, Cube, FVector(0.f, 0.f, 496.f), FRotator::ZeroRotator, FVector(18.6f, 18.6f, 0.25f), TEXT("Ceiling"), NeutralMat);

		SpawnShape(World, Cube, FVector(-341.f, 0.f, 70.f), FRotator::ZeroRotator, FVector(5.4f, 1.86f, 0.54f), TEXT("Bench_Lower"), NeutralMat);
		SpawnShape(World, Cube, FVector(310.f, -186.f, 147.f), FRotator::ZeroRotator, FVector(3.1f, 3.1f, 0.18f), TEXT("TableTop"), NeutralMat);
		SpawnShape(World, Cube, FVector(310.f, -186.f, 54.f), FRotator::ZeroRotator, FVector(0.23f, 0.23f, 1.08f), TEXT("TableLeg_FL"), NeutralMat);
		SpawnShape(World, Cube, FVector(403.f, -186.f, 54.f), FRotator::ZeroRotator, FVector(0.23f, 0.23f, 1.08f), TEXT("TableLeg_FR"), NeutralMat);
		SpawnShape(World, Cube, FVector(310.f, -279.f, 54.f), FRotator::ZeroRotator, FVector(0.23f, 0.23f, 1.08f), TEXT("TableLeg_BL"), NeutralMat);
		SpawnShape(World, Cube, FVector(403.f, -279.f, 54.f), FRotator::ZeroRotator, FVector(0.23f, 0.23f, 1.08f), TEXT("TableLeg_BR"), NeutralMat);

		const float PZ = 217.f;
		SpawnShape(World, Cube, FVector(372.f, 372.f, PZ), FRotator::ZeroRotator, FVector(0.7f, 0.7f, 4.35f), TEXT("Pillar_NE"), NeutralMat);
		SpawnShape(World, Cube, FVector(-372.f, 372.f, PZ), FRotator::ZeroRotator, FVector(0.7f, 0.7f, 4.35f), TEXT("Pillar_NW"), NeutralMat);
		SpawnShape(World, Cube, FVector(372.f, -372.f, PZ), FRotator::ZeroRotator, FVector(0.7f, 0.7f, 4.35f), TEXT("Pillar_SE"), NeutralMat);
		SpawnShape(World, Cube, FVector(-372.f, -372.f, PZ), FRotator::ZeroRotator, FVector(0.7f, 0.7f, 4.35f), TEXT("Pillar_SW"), NeutralMat);

		const int32 StairCount = FMath::Max(0, Params.StairTreadCount);
		for (int32 St = 0; St < StairCount; ++St)
		{
			TCHAR StLbl[32];
			FCString::Snprintf(StLbl, UE_ARRAY_COUNT(StLbl), TEXT("Stair_%d"), St);
			(void)SpawnShape(
				World,
				Cube,
				FVector(-558.f, -341.f + static_cast<float>(St) * 85.f, -8.f + static_cast<float>(St) * 43.f),
				FRotator(0.f, 0.f, 0.f),
				FVector(1.86f, 1.32f, 0.54f),
				StLbl,
				NeutralMat);
		}
	}

	SpawnRectLightFacingDown(World, FVector(0.f, 0.f, 472.f), 1400.f, 810.f, 7200.f, 5200.f, TEXT("RectFill_Center"));
	SpawnRectLightFacingDown(World, FVector(-341.f, 279.f, 472.f), 650.f, 435.f, 4200.f, 4800.f, TEXT("RectFill_Table"));
	SpawnRectLightFacingDown(World, FVector(403.f, -403.f, 472.f), 590.f, 590.f, 3600.f, 5500.f, TEXT("RectFill_Corner"));

	SpawnPointFill(World, FVector(0.f, 0.f, 465.f), 16000.f, 1400.f, 3800.f, TEXT("CeilingFill_Center"));
	SpawnPointFill(World, FVector(-434.f, 434.f, 403.f), 9000.f, 1100.f, 4000.f, TEXT("CeilingFill_NW"));
	SpawnPointFill(World, FVector(434.f, -434.f, 403.f), 9000.f, 1100.f, 4000.f, TEXT("CeilingFill_SE"));
	SpawnPointFill(World, FVector(434.f, 434.f, 372.f), 5000.f, 950.f, 5000.f, TEXT("CeilingFill_NE"));
}

void WorldBuilderTemplatesSampleMapBuilder::SetupOcean(UWorld* World)
{
	if (!World)
	{
		return;
	}
	const FWorldBuilderOceanParams P = WorldBuilderTemplateDefaults::MakeOceanShipped();
	FRandomStream Rand(1);
	SetupOcean(World, P, Rand);
}

void WorldBuilderTemplatesSampleMapBuilder::SetupOcean(UWorld* World, const FWorldBuilderOceanParams& Params, FRandomStream& Rand)
{
	(void)Rand;
	if (!World)
	{
		return;
	}

	UStaticMesh* Plane = LoadShapeMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
	UStaticMesh* Cone = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cone.Cone"));
	UStaticMesh* Sphere = LoadShapeMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	UMaterialInterface* NeutralMat = ResolveNeutralMaterial();

	AddSkyFromParams(World, Params.Sky);

	AddSphereReflectionCapture(World, Params.ReflectionCaptureLocation, Params.ReflectionCaptureRadius, TEXT("ReflectionCapture_Coast"));

	if (Plane)
	{
		(void)SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, Params.WaterZ),
			FRotator::ZeroRotator,
			Params.WaterPlaneScale,
			TEXT("WaterPlane"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Plane,
			FVector(1750.f, -1180.f, 3.f),
			FRotator(0.f, 25.f, 0.f),
			FVector(15.f, 12.f, 1.f),
			TEXT("ShorePlane"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Plane,
			FVector(-2100.f, 1350.f, 6.f),
			FRotator(0.f, -18.f, 0.f),
			FVector(12.f, 14.f, 1.f),
			TEXT("ShorePlane_Far"),
			NeutralMat);
	}

	if (Cone && Sphere)
	{
		(void)SpawnShape(
			World,
			Cone,
			FVector(-490.f, 280.f, 95.f),
			FRotator(0.f, 0.f, 0.f),
			FVector(3.f, 3.f, 3.6f),
			TEXT("IslandHill"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cone,
			FVector(-392.f, 448.f, 42.f),
			FRotator(0.f, 40.f, 0.f),
			FVector(1.5f, 1.5f, 1.85f),
			TEXT("IslandKnoll"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cone,
			FVector(-620.f, 180.f, 25.f),
			FRotator(0.f, -30.f, 0.f),
			FVector(1.25f, 1.25f, 1.1f),
			TEXT("IslandSpur"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Sphere,
			FVector(-448.f, 322.f, 338.f),
			FRotator::ZeroRotator,
			FVector(0.75f, 0.75f, 0.88f),
			TEXT("IslandRock"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Sphere,
			FVector(-560.f, 252.f, 72.f),
			FRotator::ZeroRotator,
			FVector(0.44f, 0.52f, 0.38f),
			TEXT("IslandRock_B"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Sphere,
			FVector(-336.f, 196.f, 52.f),
			FRotator::ZeroRotator,
			FVector(0.38f, 0.42f, 0.3f),
			TEXT("IslandRock_C"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Sphere,
			FVector(-720.f, 340.f, 48.f),
			FRotator::ZeroRotator,
			FVector(0.55f, 0.48f, 0.4f),
			TEXT("IslandRock_D"),
			NeutralMat);
	}

	SpawnPointFill(World, FVector(-434.f, 294.f, 155.f), 18000.f, 2400.f, 4200.f, TEXT("IslandWarmKey"));
	SpawnPointFill(World, FVector(560.f, 840.f, 280.f), 7500.f, 4800.f, 7500.f, TEXT("HorizonCoolRim"));
	SpawnPointFill(World, FVector(-120.f, -520.f, 95.f), 4500.f, 3200.f, 5800.f, TEXT("ShallowFill"));

	const FActorSpawnParameters ParamsFog = MakeSpawnParams();
	if (AExponentialHeightFog* Fog = World->SpawnActor<AExponentialHeightFog>(FVector::ZeroVector, FRotator::ZeroRotator, ParamsFog))
	{
		Fog->SetActorLabel(TEXT("HeightFog"));
		if (UExponentialHeightFogComponent* Fc = Fog->GetComponent())
		{
			Fc->SetFogDensity(Params.FogDensity);
			Fc->SetFogInscatteringColor(Params.FogInscatteringColor);
			Fc->SetVolumetricFog(true);
			Fc->SetVolumetricFogDistance(Params.VolumetricFogDistance);
		}
	}
}

void WorldBuilderTemplatesSampleMapBuilder::SetupCity(UWorld* World)
{
	if (!World)
	{
		return;
	}
	const FWorldBuilderCityParams P = WorldBuilderTemplateDefaults::MakeCityShipped();
	FRandomStream Rand(44077);
	SetupCity(World, P, Rand);
}

void WorldBuilderTemplatesSampleMapBuilder::SetupCity(UWorld* World, const FWorldBuilderCityParams& Params, FRandomStream& Rand)
{
	if (!World)
	{
		return;
	}

	UStaticMesh* Cube = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	UStaticMesh* Plane = LoadShapeMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));

	UMaterialInterface* GroundMat = ResolveGroundMaterial();
	UMaterialInterface* NeutralMat = ResolveNeutralMaterial();

	AddSkyFromParams(World, Params.Sky);

	AddSphereReflectionCapture(World, Params.ReflectionCaptureLocation, Params.ReflectionCaptureRadius, TEXT("ReflectionCapture_Plaza"));

	if (Plane)
	{
		(void)SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, 0.f),
			FRotator::ZeroRotator,
			Params.StreetPlaneScale,
			TEXT("StreetPlane"),
			GroundMat ? GroundMat : NeutralMat);
		(void)SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, Params.PlazaZ),
			FRotator::ZeroRotator,
			Params.PlazaPlaneScale,
			TEXT("PlazaPad"),
			NeutralMat);
	}

	const FActorSpawnParameters FogParams = MakeSpawnParams();
	if (AExponentialHeightFog* UrbanFog = World->SpawnActor<AExponentialHeightFog>(FVector::ZeroVector, FRotator::ZeroRotator, FogParams))
	{
		UrbanFog->SetActorLabel(TEXT("UrbanHaze"));
		if (UExponentialHeightFogComponent* Fc = UrbanFog->GetComponent())
		{
			Fc->SetFogDensity(Params.FogDensity);
			Fc->SetFogInscatteringColor(Params.FogInscatteringColor);
		}
	}

	const int32 N = FMath::Clamp(Params.TowerGridSize, 3, 21);
	const float Step = Params.TowerGridStep;
	const int32 Center = N / 2;

	const uint32 VarMod = static_cast<uint32>(FMath::Max(1, static_cast<int32>(Params.TowerHeightVariation)));

	TCHAR LabelBuf[64];

	for (int32 Y = 0; Y < N; ++Y)
	{
		for (int32 X = 0; X < N; ++X)
		{
			if (FMath::Abs(X - Center) <= 1 && FMath::Abs(Y - Center) <= 1)
			{
				continue;
			}

			const float ox = (static_cast<float>(X) - static_cast<float>(Center)) * Step;
			const float oy = (static_cast<float>(Y) - static_cast<float>(Center)) * Step;

			const uint32 Hash = static_cast<uint32>(X) * 73856093u ^ static_cast<uint32>(Y) * 19349663u;
			const float H = Params.TowerHeightBase + static_cast<float>(Hash % VarMod) + Rand.FRandRange(-20.f, 25.f);
			const float FootX = 0.62f + static_cast<float>((Hash >> 3) % 55u) * 0.012f;
			const float FootY = 0.62f + static_cast<float>((Hash >> 9) % 55u) * 0.012f;
			const FVector Loc(ox, oy, H * 0.5f + 15.f);
			const FVector Scale(FootX, FootY, H / 100.f);

			FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Tower_%d_%d"), X, Y);
			AStaticMeshActor* Tower = SpawnShape(World, Cube, Loc, FRotator::ZeroRotator, Scale, LabelBuf, NeutralMat);
			if (Tower && (Hash % 4u) == 0u)
			{
				const FVector CapLoc = Loc + FVector(0.f, 0.f, H * 0.5f + 32.f);
				FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Antenna_%d_%d"), X, Y);
				(void)SpawnShape(World, Cube, CapLoc, FRotator::ZeroRotator, FVector(0.1f, 0.1f, 0.55f), LabelBuf, NeutralMat);
			}
			if (Tower && (Hash % 7u) == 1u)
			{
				const FVector HeliLoc = Loc + FVector(0.f, 0.f, H * 0.5f + 18.f);
				FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("RoofBox_%d_%d"), X, Y);
				(void)SpawnShape(World, Cube, HeliLoc, FRotator::ZeroRotator, FVector(FootX * 0.85f, FootY * 0.75f, 0.12f), LabelBuf, NeutralMat);
			}
		}
	}

	const FVector PlazaTarget(0.f, 0.f, 55.f);
	SpawnSpotToward(World, FVector(1450.f, 1450.f, 780.f), PlazaTarget, 52000.f, 38.f, 5200.f, TEXT("PlazaSpot_NE"));
	SpawnSpotToward(World, FVector(-1450.f, 1450.f, 780.f), PlazaTarget, 52000.f, 38.f, 5200.f, TEXT("PlazaSpot_NW"));
	SpawnSpotToward(World, FVector(1450.f, -1450.f, 780.f), PlazaTarget, 52000.f, 38.f, 5200.f, TEXT("PlazaSpot_SE"));
	SpawnSpotToward(World, FVector(-1450.f, -1450.f, 780.f), PlazaTarget, 52000.f, 38.f, 5200.f, TEXT("PlazaSpot_SW"));

	if (Cube)
	{
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(900.f, 0.f, 0.f), TEXT("Street_N"));
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(-900.f, 0.f, 0.f), TEXT("Street_S"));
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(0.f, 900.f, 0.f), TEXT("Street_E"));
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(0.f, -900.f, 0.f), TEXT("Street_W"));
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(900.f, 900.f, 0.f), TEXT("Street_NE"));
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(-900.f, -900.f, 0.f), TEXT("Street_SW"));

		(void)SpawnShape(
			World,
			Cube,
			FVector(980.f, 0.f, 8.f),
			FRotator(0.f, 90.f, 0.f),
			FVector(0.14f, 8.2f, 0.28f),
			TEXT("Median_NS_A"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cube,
			FVector(-980.f, 0.f, 8.f),
			FRotator(0.f, 90.f, 0.f),
			FVector(0.14f, 8.2f, 0.28f),
			TEXT("Median_NS_B"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cube,
			FVector(0.f, 980.f, 8.f),
			FRotator::ZeroRotator,
			FVector(0.14f, 8.2f, 0.28f),
			TEXT("Median_EW_A"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cube,
			FVector(0.f, -980.f, 8.f),
			FRotator::ZeroRotator,
			FVector(0.14f, 8.2f, 0.28f),
			TEXT("Median_EW_B"),
			NeutralMat);
	}
}

void WorldBuilderTemplatesSampleMapBuilder::ApplyRecipe(UWorld* World, const UWorldBuilderTemplateRecipe* Recipe)
{
	if (!World || !Recipe)
	{
		return;
	}
	const int32 UseSeed = Recipe->Seed == 0 ? (FMath::Rand() & 0x7FFFFFFF) : Recipe->Seed;
	FRandomStream Rand(UseSeed);
	switch (Recipe->TemplateKind)
	{
	case EWorldBuilderTemplateKind::Outdoor:
		SetupOutdoor(World, Recipe->Outdoor, Rand);
		break;
	case EWorldBuilderTemplateKind::IndoorBlockout:
		SetupIndoorBlockout(World, Recipe->Indoor, Rand);
		break;
	case EWorldBuilderTemplateKind::Ocean:
		SetupOcean(World, Recipe->Ocean, Rand);
		break;
	case EWorldBuilderTemplateKind::City:
		SetupCity(World, Recipe->City, Rand);
		break;
	default:
		break;
	}
}
