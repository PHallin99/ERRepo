// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EndlessRunnerCharacter.generated.h"


UCLASS(config=Game)
class AEndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AEndlessRunnerCharacter();

	TObjectPtr<UStaticMeshComponent> PlayerMesh;


	UPROPERTY()
	float MovementSpeed;
protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

private:
};
