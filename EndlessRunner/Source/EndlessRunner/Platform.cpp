#include "Platform.h"

#include "EndlessRunnerGameMode.h"

APlatform::APlatform()
{
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* TransformComponent = CreateDefaultSubobject<USceneComponent>(TEXT("TransformComponent"));
	RootComponent = TransformComponent;

	PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>("PlatformMesh");

	if (static ConstructorHelpers::FObjectFinder<UStaticMesh> CubeMesh(TEXT("/Engine/BasicShapes/Cube")); CubeMesh.
		Succeeded())
	{
		PlatformMesh->SetStaticMesh(CubeMesh.Object);
	}

	PlatformMesh->SetRelativeScale3D(FVector(1.f, 1.f, 1.f));
	PlatformMesh->SetupAttachment(TransformComponent);
}

void APlatform::SetLaneIndex(int Index)
{
	LaneIndex = Index;
}

void APlatform::BeginPlay()
{
	Super::BeginPlay();
}

void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector MovementOffset = MovementDirection * MovementSpeed * DeltaTime;
	SetActorLocation(GetActorLocation() + MovementOffset);

	if (GetActorLocation().X < 910 && GetActorLocation().X > 710)
	{
		EndlessRunnerGameMode->CheckCollision(this);
	}

	if (GetActorLocation().X > 500)
	{
		return;
	}

	if (EndlessRunnerGameMode)
	{
		EndlessRunnerGameMode->AddScore(1);
	}
	Destroy();
}
