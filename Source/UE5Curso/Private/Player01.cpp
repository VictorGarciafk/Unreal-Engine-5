
#include "Player01.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"

// Sets default values
APlayer01::APlayer01()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	
	//
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.0f;
	SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	CameraComponent->bUsePawnControlRotation = false;
	
}

// Called when the game starts or when spawned
void APlayer01::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* playerController = Cast<APlayerController>(Controller);
	if (!IsValid(playerController)) return;

	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(playerController->GetLocalPlayer());
	if (!IsValid(Subsystem)) return;

	Subsystem->AddMappingContext(DefaultMappingContext,0);
	/*
	//mostramos en pantalla un mensaje al iniciar el juego
	GEngine->AddOnScreenDebugMessage(-1,10.0f, FColor::Blue, TEXT("Hellouda Player"));

	//Escribimos en el archivo LOG un mensaje al ejecutar el juego
	UE_LOG(LogTemp, Log, TEXT("Hellouda Player"));
	*/
	
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

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	if (!IsValid(EnhancedInputComponent)) return;

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &APlayer01::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APlayer01::Look);

	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
}

void APlayer01::Move(const FInputActionValue& InputActionValue) {
	//UE_LOG(LogTemp, Log, TEXT("MOVE!!"));

	if (!IsValid(Controller)) return;
	FVector2D movementVector = InputActionValue.Get<FVector2d>();

	const FRotator rotation = Controller->GetControlRotation();
	const FRotator yawRotation = FRotator(0,rotation.Yaw,0);

	const FVector forwardDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::X);
	const FVector rigDirection = FRotationMatrix(yawRotation).GetUnitAxis(EAxis::Y);

	AddMovementInput(forwardDirection, movementVector.Y);
	AddMovementInput(rigDirection, movementVector.X);
}

void APlayer01::Look(const FInputActionValue& InputActionValue)
{
	if (!IsValid(Controller)) return;
	FVector2D LookVector = InputActionValue.Get<FVector2d>();
	
	//eje x(Horizontal)
	AddControllerYawInput(LookVector.X);

	//eje y(Vertical)
	AddControllerPitchInput(LookVector.Y);

}
