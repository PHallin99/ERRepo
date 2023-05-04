#include "ER_Factory.h"
#include "Platform.h"

AER_Factory::AER_Factory()
{
	PrimaryActorTick.bCanEverTick = true;
	SpawnLocations.Add(FVector(3950, 800, 140));
	SpawnLocations.Add(FVector(3950, 1200, 140));
	SpawnLocations.Add(FVector(3950, 1600, 140));
}

void AER_Factory::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(PlatformSpawnTimer, this, &AER_Factory::SpawnPlatform, 3.f, true);
	SpawnPlatform();
}

void AER_Factory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AER_Factory::SpawnPlatform()
{
	const FVector SpawnLocation = SpawnLocations[FMath::RandRange(0, 2)];
	const FRotator SpawnRotation(GetActorRotation());
	const FActorSpawnParameters SpawnParams;

	if (AActor* SpawnedActor = GetWorld()->SpawnActor<APlatform>(APlatform::StaticClass(), SpawnLocation, SpawnRotation,
	                                                             SpawnParams))
	{
		APlatform* SpawnedPlatform = Cast<APlatform>(SpawnedActor);
		SpawnedActor->SetActorScale3D(FVector(1.f, 4.f, 1.f));
		SpawnedPlatform->MovementDirection = FVector(-1.f, 0.f, 0.f);
		SpawnedPlatform->MovementSpeed = 500.f;
		SpawnedPlatforms.Add(SpawnedPlatform);
	}
}
