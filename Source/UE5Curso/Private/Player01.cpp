#include "Player01.h"


// Sets default values
APlayer01::APlayer01()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void APlayer01::BeginPlay()
{
	Super::BeginPlay();
	
	//mostramos en pantalla un mensaje al iniciar el juego
	GEngine->AddOnScreenDebugMessage(-1,10.0f, FColor::Blue, TEXT("Hellouda Player"));

	//Escribimos en el archivo LOG un mensaje al ejecutar el juego
	UE_LOG(LogTemp, Log, TEXT("Hellouda Player"));
}

// Called every frame
/*void APlayer01::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}*/

// Called to bind functionality to input
void APlayer01::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


