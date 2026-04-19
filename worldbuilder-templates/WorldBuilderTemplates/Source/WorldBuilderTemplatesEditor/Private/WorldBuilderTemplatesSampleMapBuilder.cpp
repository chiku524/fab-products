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
		UMaterialInterface* FallbackMat)
	{
		if (!World || !Cylinder || !Cone)
		{
			return;
		}
		TCHAR LabelBuf[64];
		FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Tree_%d_Trunk"), Index);
		(void)SpawnShape(
			World,
			Cylinder,
			Base + FVector(0.f, 0.f, 140.f),
			FRotator::ZeroRotator,
			FVector(0.22f, 0.22f, 1.4f),
			LabelBuf,
			TrunkMat ? TrunkMat : FallbackMat);
		FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Tree_%d_Canopy"), Index);
		(void)SpawnShape(
			World,
			Cone,
			Base + FVector(0.f, 0.f, 360.f),
			FRotator(0.f, 0.f, 0.f),
			FVector(1.1f, 1.1f, 1.35f),
			LabelBuf,
			CanopyMat ? CanopyMat : FallbackMat);
	}

	void SpawnRockCluster(UWorld* World, UStaticMesh* Sphere, UMaterialInterface* Mat, const FVector& Base, int32 ClusterIndex, FRandomStream& Rand)
	{
		if (!World || !Sphere)
		{
			return;
		}
		const int32 Num = 2 + (Rand.GetFraction() > 0.5f ? 1 : 0);
		for (int32 i = 0; i < Num; ++i)
		{
			const float ox = Rand.FRandRange(-120.f, 120.f);
			const float oy = Rand.FRandRange(-120.f, 120.f);
			const float s = Rand.FRandRange(0.35f, 0.85f);
			TCHAR LabelBuf[64];
			FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Rock_%d_%d"), ClusterIndex, i);
			(void)SpawnShape(
				World,
				Sphere,
				Base + FVector(ox, oy, 40.f * s),
				FRotator(Rand.FRandRange(-8.f, 8.f), Rand.FRandRange(0.f, 360.f), Rand.FRandRange(-8.f, 8.f)),
				FVector(s, s * Rand.FRandRange(0.85f, 1.15f), s * 0.75f),
				LabelBuf,
				Mat);
		}
	}
}

void WorldBuilderTemplatesSampleMapBuilder::SetupOutdoor(UWorld* World)
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

	AddSkySunCloudsAndPost(
		World,
		-42.f,
		48.f,
		9.f,
		5800.f,
		1.65f,
		true,
		0.92f,
		FLinearColor(1.f, 0.99f, 0.96f, 1.f),
		true,
		0.24f,
		-1.f);

	AddSphereReflectionCapture(World, FVector(120.f, -80.f, 160.f), 3200.f, TEXT("ReflectionCapture_Main"));

	const FActorSpawnParameters FogParamsOutdoor = MakeSpawnParams();
	if (AExponentialHeightFog* Mist = World->SpawnActor<AExponentialHeightFog>(FVector::ZeroVector, FRotator::ZeroRotator, FogParamsOutdoor))
	{
		Mist->SetActorLabel(TEXT("GroundMist"));
		if (UExponentialHeightFogComponent* Fc = Mist->GetComponent())
		{
			Fc->SetFogDensity(0.006f);
			Fc->SetFogInscatteringColor(FLinearColor(0.72f, 0.78f, 0.88f));
		}
	}

	if (Plane)
	{
		AStaticMeshActor* Ground = SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, 0.f),
			FRotator::ZeroRotator,
			FVector(14.f, 14.f, 1.f),
			TEXT("GroundPlane"),
			GroundMat ? GroundMat : NeutralMat);
		(void)Ground;
	}

	FRandomStream OutdoorRand(91021);
	const FVector TreeBases[] = {
		FVector(-420.f, 280.f, 0.f),
		FVector(380.f, -310.f, 0.f),
		FVector(-180.f, -520.f, 0.f),
		FVector(520.f, 420.f, 0.f),
		FVector(-650.f, -150.f, 0.f),
	};
	for (int32 i = 0; i < UE_ARRAY_COUNT(TreeBases); ++i)
	{
		SpawnStylizedTree(World, Cylinder, Cone, NeutralMat, NeutralMat, TreeBases[i], i, NeutralMat);
	}

	if (Cube)
	{
		for (int32 s = 0; s < 9; ++s)
		{
			const float t = static_cast<float>(s) - 4.f;
			TCHAR StepLbl[32];
			FCString::Snprintf(StepLbl, UE_ARRAY_COUNT(StepLbl), TEXT("PathStone_%d"), s);
			(void)SpawnShape(
				World,
				Cube,
				FVector(-180.f + t * 95.f, 40.f, 8.f),
				FRotator(0.f, 12.f * t, 0.f),
				FVector(0.42f, 0.35f, 0.12f),
				StepLbl,
				NeutralMat);
		}
		(void)SpawnShape(
			World,
			Cube,
			FVector(520.f, -180.f, 45.f),
			FRotator(0.f, -18.f, 0.f),
			FVector(4.5f, 2.2f, 0.55f),
			TEXT("TerracePad"),
			NeutralMat);
	}

	for (int32 c = 0; c < 4; ++c)
	{
		const float ox = OutdoorRand.FRandRange(-700.f, 700.f);
		const float oy = OutdoorRand.FRandRange(-700.f, 700.f);
		SpawnRockCluster(World, Sphere, NeutralMat, FVector(ox, oy, 0.f), c, OutdoorRand);
	}

	SpawnPointFill(World, FVector(-200.f, -120.f, 220.f), 8500.f, 1400.f, 5000.f, TEXT("FillWarm"));
	SpawnPointFill(World, FVector(250.f, 180.f, 180.f), 4500.f, 1200.f, 7500.f, TEXT("FillCool"));
}

void WorldBuilderTemplatesSampleMapBuilder::SetupIndoorBlockout(UWorld* World)
{
	if (!World)
	{
		return;
	}

	UStaticMesh* Cube = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	UStaticMesh* Plane = LoadShapeMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));

	UMaterialInterface* GroundMat = ResolveGroundMaterial();
	UMaterialInterface* NeutralMat = ResolveNeutralMaterial();

	AddSkySunCloudsAndPost(
		World,
		-72.f,
		15.f,
		2.2f,
		4200.f,
		0.85f,
		false,
		0.88f,
		FLinearColor(1.f, 0.97f, 0.92f, 1.f),
		true,
		0.2f,
		-1.f);

	AddSphereReflectionCapture(World, FVector(0.f, 0.f, 140.f), 2200.f, TEXT("ReflectionCapture_Room"));

	if (Plane)
	{
		(void)SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, -20.f),
			FRotator::ZeroRotator,
			FVector(8.f, 8.f, 1.f),
			TEXT("Floor"),
			GroundMat ? GroundMat : NeutralMat);
	}

	if (Cube)
	{
		SpawnShape(World, Cube, FVector(-300.f, 400.f, 150.f), FRotator::ZeroRotator, FVector(5.f, 0.5f, 3.f), TEXT("Wall_North_L"), NeutralMat);
		SpawnShape(World, Cube, FVector(300.f, 400.f, 150.f), FRotator::ZeroRotator, FVector(5.f, 0.5f, 3.f), TEXT("Wall_North_R"), NeutralMat);
		SpawnShape(World, Cube, FVector(0.f, -400.f, 150.f), FRotator::ZeroRotator, FVector(12.f, 0.5f, 3.f), TEXT("Wall_South"), NeutralMat);
		SpawnShape(World, Cube, FVector(400.f, 0.f, 150.f), FRotator(0.f, 90.f, 0.f), FVector(12.f, 0.5f, 3.f), TEXT("Wall_East"), NeutralMat);
		SpawnShape(World, Cube, FVector(-400.f, 0.f, 150.f), FRotator(0.f, 90.f, 0.f), FVector(12.f, 0.5f, 3.f), TEXT("Wall_West"), NeutralMat);
		SpawnShape(World, Cube, FVector(0.f, 0.f, 320.f), FRotator::ZeroRotator, FVector(12.f, 12.f, 0.25f), TEXT("Ceiling"), NeutralMat);

		SpawnShape(World, Cube, FVector(-220.f, 0.f, 45.f), FRotator::ZeroRotator, FVector(3.5f, 1.2f, 0.35f), TEXT("Bench_Lower"), NeutralMat);
		SpawnShape(World, Cube, FVector(200.f, -120.f, 95.f), FRotator::ZeroRotator, FVector(2.f, 2.f, 0.12f), TEXT("TableTop"), NeutralMat);
		SpawnShape(World, Cube, FVector(200.f, -120.f, 35.f), FRotator::ZeroRotator, FVector(0.15f, 0.15f, 0.7f), TEXT("TableLeg_FL"), NeutralMat);
		SpawnShape(World, Cube, FVector(260.f, -120.f, 35.f), FRotator::ZeroRotator, FVector(0.15f, 0.15f, 0.7f), TEXT("TableLeg_FR"), NeutralMat);
		SpawnShape(World, Cube, FVector(200.f, -180.f, 35.f), FRotator::ZeroRotator, FVector(0.15f, 0.15f, 0.7f), TEXT("TableLeg_BL"), NeutralMat);
		SpawnShape(World, Cube, FVector(260.f, -180.f, 35.f), FRotator::ZeroRotator, FVector(0.15f, 0.15f, 0.7f), TEXT("TableLeg_BR"), NeutralMat);

		const float PZ = 140.f;
		SpawnShape(World, Cube, FVector(240.f, 240.f, PZ), FRotator::ZeroRotator, FVector(0.45f, 0.45f, 2.8f), TEXT("Pillar_NE"), NeutralMat);
		SpawnShape(World, Cube, FVector(-240.f, 240.f, PZ), FRotator::ZeroRotator, FVector(0.45f, 0.45f, 2.8f), TEXT("Pillar_NW"), NeutralMat);
		SpawnShape(World, Cube, FVector(240.f, -240.f, PZ), FRotator::ZeroRotator, FVector(0.45f, 0.45f, 2.8f), TEXT("Pillar_SE"), NeutralMat);
		SpawnShape(World, Cube, FVector(-240.f, -240.f, PZ), FRotator::ZeroRotator, FVector(0.45f, 0.45f, 2.8f), TEXT("Pillar_SW"), NeutralMat);

		for (int32 St = 0; St < 4; ++St)
		{
			TCHAR StLbl[32];
			FCString::Snprintf(StLbl, UE_ARRAY_COUNT(StLbl), TEXT("Stair_%d"), St);
			(void)SpawnShape(
				World,
				Cube,
				FVector(-360.f, -220.f + static_cast<float>(St) * 55.f, -5.f + static_cast<float>(St) * 28.f),
				FRotator(0.f, 0.f, 0.f),
				FVector(1.2f, 0.85f, 0.35f),
				StLbl,
				NeutralMat);
		}
	}

	SpawnRectLightFacingDown(World, FVector(0.f, 0.f, 305.f), 900.f, 520.f, 5800.f, 5200.f, TEXT("RectFill_Center"));
	SpawnRectLightFacingDown(World, FVector(-220.f, 180.f, 305.f), 420.f, 280.f, 3200.f, 4800.f, TEXT("RectFill_Table"));
	SpawnRectLightFacingDown(World, FVector(260.f, -260.f, 305.f), 380.f, 380.f, 2800.f, 5500.f, TEXT("RectFill_Corner"));

	SpawnPointFill(World, FVector(0.f, 0.f, 300.f), 12000.f, 900.f, 3800.f, TEXT("CeilingFill_Center"));
	SpawnPointFill(World, FVector(-280.f, 280.f, 260.f), 6500.f, 700.f, 4000.f, TEXT("CeilingFill_NW"));
	SpawnPointFill(World, FVector(280.f, -280.f, 260.f), 6500.f, 700.f, 4000.f, TEXT("CeilingFill_SE"));
}

void WorldBuilderTemplatesSampleMapBuilder::SetupOcean(UWorld* World)
{
	if (!World)
	{
		return;
	}

	UStaticMesh* Plane = LoadShapeMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));
	UStaticMesh* Cone = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cone.Cone"));
	UStaticMesh* Sphere = LoadShapeMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));

	UMaterialInterface* NeutralMat = ResolveNeutralMaterial();

	AddSkySunCloudsAndPost(
		World,
		-35.f,
		-40.f,
		10.f,
		7200.f,
		1.8f,
		true,
		0.9f,
		FLinearColor(0.92f, 0.96f, 1.f, 1.f),
		true,
		0.22f,
		0.06f);

	AddSphereReflectionCapture(World, FVector(-200.f, 100.f, 90.f), 4500.f, TEXT("ReflectionCapture_Coast"));

	if (Plane)
	{
		(void)SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, -5.f),
			FRotator::ZeroRotator,
			FVector(28.f, 28.f, 1.f),
			TEXT("WaterPlane"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Plane,
			FVector(1200.f, -800.f, 2.f),
			FRotator(0.f, 25.f, 0.f),
			FVector(10.f, 8.f, 1.f),
			TEXT("ShorePlane"),
			NeutralMat);
	}

	if (Cone && Sphere)
	{
		(void)SpawnShape(
			World,
			Cone,
			FVector(-350.f, 200.f, 80.f),
			FRotator(0.f, 0.f, 0.f),
			FVector(2.2f, 2.2f, 2.8f),
			TEXT("IslandHill"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cone,
			FVector(-280.f, 320.f, 35.f),
			FRotator(0.f, 40.f, 0.f),
			FVector(1.1f, 1.1f, 1.4f),
			TEXT("IslandKnoll"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Sphere,
			FVector(-320.f, 230.f, 260.f),
			FRotator::ZeroRotator,
			FVector(0.55f, 0.55f, 0.65f),
			TEXT("IslandRock"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Sphere,
			FVector(-400.f, 180.f, 55.f),
			FRotator::ZeroRotator,
			FVector(0.32f, 0.38f, 0.28f),
			TEXT("IslandRock_B"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Sphere,
			FVector(-240.f, 140.f, 40.f),
			FRotator::ZeroRotator,
			FVector(0.28f, 0.3f, 0.22f),
			TEXT("IslandRock_C"),
			NeutralMat);
	}

	SpawnPointFill(World, FVector(-310.f, 210.f, 120.f), 14000.f, 1600.f, 4200.f, TEXT("IslandWarmKey"));
	SpawnPointFill(World, FVector(400.f, 600.f, 220.f), 5500.f, 3500.f, 7500.f, TEXT("HorizonCoolRim"));

	const FActorSpawnParameters Params = MakeSpawnParams();
	if (AExponentialHeightFog* Fog = World->SpawnActor<AExponentialHeightFog>(FVector::ZeroVector, FRotator::ZeroRotator, Params))
	{
		Fog->SetActorLabel(TEXT("HeightFog"));
		if (UExponentialHeightFogComponent* Fc = Fog->GetComponent())
		{
			Fc->SetFogDensity(0.028f);
			Fc->SetFogInscatteringColor(FLinearColor(0.12f, 0.32f, 0.52f));
			Fc->SetVolumetricFog(true);
			Fc->SetVolumetricFogDistance(6000.f);
		}
	}
}

void WorldBuilderTemplatesSampleMapBuilder::SetupCity(UWorld* World)
{
	if (!World)
	{
		return;
	}

	UStaticMesh* Cube = LoadShapeMesh(TEXT("/Engine/BasicShapes/Cube.Cube"));
	UStaticMesh* Plane = LoadShapeMesh(TEXT("/Engine/BasicShapes/Plane.Plane"));

	UMaterialInterface* GroundMat = ResolveGroundMaterial();
	UMaterialInterface* NeutralMat = ResolveNeutralMaterial();

	AddSkySunCloudsAndPost(
		World,
		-48.f,
		55.f,
		7.5f,
		6200.f,
		1.45f,
		true,
		0.9f,
		FLinearColor(0.98f, 0.98f, 1.f, 1.f),
		true,
		0.17f,
		0.12f);

	AddSphereReflectionCapture(World, FVector(0.f, 0.f, 120.f), 2800.f, TEXT("ReflectionCapture_Plaza"));

	if (Plane)
	{
		(void)SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, 0.f),
			FRotator::ZeroRotator,
			FVector(18.f, 18.f, 1.f),
			TEXT("StreetPlane"),
			GroundMat ? GroundMat : NeutralMat);
		(void)SpawnShape(
			World,
			Plane,
			FVector(0.f, 0.f, 8.f),
			FRotator::ZeroRotator,
			FVector(9.f, 9.f, 1.f),
			TEXT("PlazaPad"),
			NeutralMat);
	}

	const FActorSpawnParameters FogParams = MakeSpawnParams();
	if (AExponentialHeightFog* UrbanFog = World->SpawnActor<AExponentialHeightFog>(FVector::ZeroVector, FRotator::ZeroRotator, FogParams))
	{
		UrbanFog->SetActorLabel(TEXT("UrbanHaze"));
		if (UExponentialHeightFogComponent* Fc = UrbanFog->GetComponent())
		{
			Fc->SetFogDensity(0.012f);
			Fc->SetFogInscatteringColor(FLinearColor(0.55f, 0.58f, 0.62f));
		}
	}

	const int32 N = 7;
	const float Step = 320.f;
	const int32 Center = N / 2;

	TCHAR LabelBuf[64];
	FRandomStream CityRand(44077);

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
			const float H = 95.f + static_cast<float>(Hash % 280u) + CityRand.FRandRange(-15.f, 15.f);
			const float FootX = 0.55f + static_cast<float>((Hash >> 3) % 60u) * 0.01f;
			const float FootY = 0.55f + static_cast<float>((Hash >> 9) % 60u) * 0.01f;
			const FVector Loc(ox, oy, H * 0.5f + 12.f);
			const FVector Scale(FootX, FootY, H / 100.f);

			FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Tower_%d_%d"), X, Y);
			AStaticMeshActor* Tower = SpawnShape(World, Cube, Loc, FRotator::ZeroRotator, Scale, LabelBuf, NeutralMat);
			if (Tower && (Hash % 5u) == 0u)
			{
				const FVector CapLoc = Loc + FVector(0.f, 0.f, H * 0.5f + 25.f);
				FCString::Snprintf(LabelBuf, UE_ARRAY_COUNT(LabelBuf), TEXT("Antenna_%d_%d"), X, Y);
				(void)SpawnShape(World, Cube, CapLoc, FRotator::ZeroRotator, FVector(0.08f, 0.08f, 0.45f), LabelBuf, NeutralMat);
			}
		}
	}

	const FVector PlazaTarget(0.f, 0.f, 40.f);
	SpawnSpotToward(World, FVector(950.f, 950.f, 620.f), PlazaTarget, 48000.f, 38.f, 5200.f, TEXT("PlazaSpot_NE"));
	SpawnSpotToward(World, FVector(-950.f, 950.f, 620.f), PlazaTarget, 48000.f, 38.f, 5200.f, TEXT("PlazaSpot_NW"));
	SpawnSpotToward(World, FVector(950.f, -950.f, 620.f), PlazaTarget, 48000.f, 38.f, 5200.f, TEXT("PlazaSpot_SE"));
	SpawnSpotToward(World, FVector(-950.f, -950.f, 620.f), PlazaTarget, 48000.f, 38.f, 5200.f, TEXT("PlazaSpot_SW"));

	if (Cube)
	{
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(580.f, 0.f, 0.f), TEXT("Street_N"));
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(-580.f, 0.f, 0.f), TEXT("Street_S"));
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(0.f, 580.f, 0.f), TEXT("Street_E"));
		SpawnStreetLamp(World, Cube, NeutralMat, FVector(0.f, -580.f, 0.f), TEXT("Street_W"));

		(void)SpawnShape(
			World,
			Cube,
			FVector(620.f, 0.f, 6.f),
			FRotator(0.f, 90.f, 0.f),
			FVector(0.12f, 5.5f, 0.22f),
			TEXT("Median_NS_A"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cube,
			FVector(-620.f, 0.f, 6.f),
			FRotator(0.f, 90.f, 0.f),
			FVector(0.12f, 5.5f, 0.22f),
			TEXT("Median_NS_B"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cube,
			FVector(0.f, 620.f, 6.f),
			FRotator::ZeroRotator,
			FVector(0.12f, 5.5f, 0.22f),
			TEXT("Median_EW_A"),
			NeutralMat);
		(void)SpawnShape(
			World,
			Cube,
			FVector(0.f, -620.f, 6.f),
			FRotator::ZeroRotator,
			FVector(0.12f, 5.5f, 0.22f),
			TEXT("Median_EW_B"),
			NeutralMat);
	}
}
