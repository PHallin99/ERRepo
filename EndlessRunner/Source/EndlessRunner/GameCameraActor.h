// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "GameCameraActor.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API AGameCameraActor : public ACameraActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
};
