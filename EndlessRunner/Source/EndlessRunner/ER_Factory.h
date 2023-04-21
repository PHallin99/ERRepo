#pragma once

#include "CoreMinimal.h"
#include "../../../../../../../../../Program Files (x86)/Microsoft Visual Studio/2019/Community/VC/Tools/MSVC/14.29.30133/INCLUDE/memory"
#include "GameFramework/Actor.h"
#include "ER_Factory.generated.h"

UCLASS()
class ENDLESSRUNNER_API AER_Factory : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AER_Factory();
	TArray<TObjectPtr<AActor>> SpawnedPlatforms;			// Array of spawned platforms

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
