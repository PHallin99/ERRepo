#pragma once

#include "CoreMinimal.h"
#include "EndlessRunnerGameMode.h"
#include "../../../../../../../../../Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/INCLUDE/memory"
#include "GameFramework/Actor.h"
#include "ER_Factory.generated.h"

class AEndlessRunnerGameMode;
class APlatform;

UCLASS()
class ENDLESSRUNNER_API AER_Factory : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AER_Factory();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlatformMovementSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float PlatformSpawnInterval;

	AEndlessRunnerGameMode* ERGameMode;

	void Stop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	TArray<APlatform*> SpawnedPlatforms;
	TArray<FVector> SpawnLocations;
	void SpawnPlatform();
	FTimerHandle PlatformSpawnTimer;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void RemoveAll();
};
