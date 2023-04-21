﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "Platform.h"


// Sets default values
APlatform::APlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PlatformMesh = CreateDefaultSubobject<UMeshComponent>("PlatformMesh");
}

// Called when the game starts or when spawned
void APlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

