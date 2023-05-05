// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerCharacter.h"
#include "GameFramework/GameModeBase.h"
#include "EndlessRunnerGameMode.generated.h"

class APlatform;
class AER_Factory;

UCLASS(minimalapi)
class AEndlessRunnerGameMode : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	int SessionScore;

protected:
	void SetupCamera() const;
	void SpawnPlayers();
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Players")
	TObjectPtr<AEndlessRunnerCharacter> Player1;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Players")
	TObjectPtr<AEndlessRunnerCharacter> Player2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AER_Factory> PlatformFactory;

public:
	AEndlessRunnerGameMode();
	void AddScore(int Score);
	void CheckCollision(APlatform* Platform);
};
