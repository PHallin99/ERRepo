#include "Platform.h"

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

void APlatform::BeginPlay()
{
	Super::BeginPlay();
}

void APlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	const FVector MovementOffset = MovementDirection * MovementSpeed * DeltaTime;
	SetActorLocation(GetActorLocation() + MovementOffset);
	if (GetActorLocation().Y > 100)
	{
		return;
	}

	Destroy();
}
