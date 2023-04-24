#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Platform.generated.h"

UCLASS()
class ENDLESSRUNNER_API APlatform : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> PlatformMesh;

public:
	APlatform();
	FVector MovementDirection;
	float MovementSpeed;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override; // Have actor move in runtime as initialized
};
