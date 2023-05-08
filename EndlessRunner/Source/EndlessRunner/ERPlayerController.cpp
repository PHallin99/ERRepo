// Fill out your copyright notice in the Description page of Project Settings.


#include "ERPlayerController.h"

// Sets default values
AERPlayerController::AERPlayerController()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
}

// Called when the game starts or when spawned
void AERPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AERPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

