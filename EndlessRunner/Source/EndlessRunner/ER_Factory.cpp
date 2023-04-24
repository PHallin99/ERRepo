#include "ER_Factory.h"
#include "Platform.h"

AER_Factory::AER_Factory()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AER_Factory::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(PlatformSpawnTimer, this, &AER_Factory::SpawnPlatform, 10.f, true);
	SpawnPlatform();
}

void AER_Factory::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AER_Factory::SpawnPlatform()
{
	const FVector SpawnLocation(GetActorLocation());
	const FRotator SpawnRotation(GetActorRotation());
	const FActorSpawnParameters SpawnParams;

	if (AActor* SpawnedActor = GetWorld()->SpawnActor<APlatform>(APlatform::StaticClass(), SpawnLocation, SpawnRotation, SpawnParams))
	{
		APlatform* SpawnedPlatform = Cast<APlatform>(SpawnedActor);
		SpawnedPlatform->MovementDirection = FVector(0.f, -1.f, 0.f);
		SpawnedPlatform->MovementSpeed = 20.f;
		SpawnedPlatforms.Add(SpawnedPlatform);
	}
}
