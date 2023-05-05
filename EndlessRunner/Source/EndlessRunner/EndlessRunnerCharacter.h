// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EndlessRunnerCharacter.generated.h"


UCLASS(config=Game)
class AEndlessRunnerCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TArray<FVector> LanePositions;

	void MoveLeft();
	void MoveRight();
	void OnParry();
	void SetupCharacterActor();
	void SetLanePositions();

	UPROPERTY(EditAnywhere)
	UPlayerInput* PlayerInput;

public:
	AEndlessRunnerCharacter();
	TObjectPtr<UStaticMeshComponent> PlayerMesh;
	void SetLaneIndex(int Index);

	UPROPERTY()
	float MovementSpeed;

	UPROPERTY(EditAnywhere)
	int LaneIndex;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

public:
	virtual void Tick(float DeltaTime) override;
};
