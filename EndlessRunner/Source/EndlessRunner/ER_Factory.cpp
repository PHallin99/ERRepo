#include "ER_Factory.h"
#include "Platform.h"

AER_Factory::AER_Factory()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AER_Factory::BeginPlay()
{
	Super::BeginPlay();

	SpawnPlatform();
}

void AER_Factory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AER_Factory::SpawnPlatform() const
{
	const FVector SpawnLocation(GetActorLocation());
	const FVector SpawnRotation(0.f, 0.f, 0.f);
	const FActorSpawnParameters SpawnParams;

	if (AActor* SpawnedActor = GetWorld()->SpawnActor<APlatform>(APlatform::StaticClass(), SpawnLocation,
	                                                             SpawnRotation.Rotation(), SpawnParams))
	{
		APlatform* SpawnedPlatform = Cast<APlatform>(SpawnedActor);
		SpawnedPlatform->MovementDirection = FVector(0.f, -1.f, 0.f);
		SpawnedPlatform->MovementSpeed = 10.f;
	}
}
