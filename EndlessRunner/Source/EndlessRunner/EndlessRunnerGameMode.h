// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerCharacter.h"
#include "LifeBox.h"
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

	UPROPERTY(EditAnywhere)
	int LivesLeft;

	UPROPERTY(EditAnywhere)
	TArray<ALifeBox*> LivesBoxes;

	AEndlessRunnerCharacter* Player1Spawned;
	AEndlessRunnerCharacter* Player2Spawned;

	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerController> ERPlayerControllerBP;

protected:
	void SetupCamera() const;
	void SpawnPlayers();
	void SpawnFactory();
	void SpawnLives();
	void UpdateHighScoreUI() const;
	virtual void BeginPlay() override;


	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<AER_Factory> PlatformFactory;

public:
	AEndlessRunnerGameMode();
	void AddScore(int Score);
	void RemoveLife();
	void ParryAttempt(int LaneIndex) const;
	bool CheckCollision(const APlatform* Platform) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Players")
	TSubclassOf<ACharacter> BPEndlessCharacter;
};
