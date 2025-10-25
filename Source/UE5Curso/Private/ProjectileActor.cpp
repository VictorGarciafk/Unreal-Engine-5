


#include "ProjectileActor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"


// Sets default values
AProjectileActor::AProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("ProjectileMeshComponent");
	SetRootComponent(ProjectileMeshComponent);
	ProjectileMeshComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);

	ProjectileCollisionComponent = CreateDefaultSubobject<USphereComponent>("ProjectileCollisionComponent");
	ProjectileCollisionComponent->SetupAttachment(RootComponent);
	ProjectileCollisionComponent->SetCollisionProfileName("BlockAll");

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	ProjectileMovementComponent->InitialSpeed = 750.0f;

	
}

// Called when the game starts or when spawned 
void AProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	
	ProjectileCollisionComponent->OnComponentHit.AddUniqueDynamic(this, &AProjectileActor::OnProjectHit);
}

void AProjectileActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ProjectileCollisionComponent->OnComponentHit.RemoveAll(this);
}

void AProjectileActor::OnProjectHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	Destroy();
}



