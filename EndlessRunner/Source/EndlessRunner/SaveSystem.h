// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "SaveSystem.generated.h"

/**
 * 
 */
UCLASS()
class ENDLESSRUNNER_API USaveSystem : public UObject
{
	GENERATED_BODY()
public:
	static void SaveScore(int Score);
	static int LoadScore();
};
