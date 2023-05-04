// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ERPlayerController.generated.h"

UCLASS()
class ENDLESSRUNNER_API AERPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AERPlayerController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	void OnLeftPressed();
	void OnLeftAPressed();
	void OnRightPressed();
	void OnRightDPressed();
	void OnJumpPressed();
	void OnJumpWPressed();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
