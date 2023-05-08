// Fill out your copyright notice in the Description page of Project Settings.


#include "LifeBox.h"


// Sets default values
ALifeBox::ALifeBox()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");

	if (static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube")); CubeMesh.
		Succeeded())
	{
		StaticMesh->SetStaticMesh(CubeMesh.Object);
	}

	StaticMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
}

// Called when the game starts or when spawned
void ALifeBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ALifeBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

