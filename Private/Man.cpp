// Fill out your copyright notice in the Description page of Project Settings.


#include "Man.h"
#if 1
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#endif
#if 1
#include "GameFramework/Controller.h"
#include "Engine/World.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#endif

// Sets default values
AMan::AMan()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength=600;
	SpringArmComp->bUsePawnControlRotation=true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArmComp,USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;

	BaseTurnRate = 65;
	BaseLookupRate = 65;
	// 角色的旋转不由Controller控制
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f,540,0);// 转身速率
	GetCharacterMovement()->JumpZVelocity = 650;// 跳跃初始速度
	GetCharacterMovement()->AirControl = 0.2f;// 在跳跃中的控制量
}

void AMan::MoveForward(float Value)
{
	if (Controller && Value != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();// 拿到控制器的旋转
		const FRotator YawRotation(0.f,Rotation.Yaw,0);// 以这个旋转值构造一个旋转
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);// 用这个旋转构造了一个旋转矩阵
		AddMovementInput(Direction,Value);
	}
}

void AMan::MoveRight(float Value)
{
	if (Controller && Value != 0)
	{
		const FRotator Rotation = Controller->GetControlRotation();// 拿到控制器的旋转
		const FRotator YawRotation(0.f,Rotation.Yaw,0);// 以这个旋转值构造一个旋转
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);// 用这个旋转构造了一个旋转矩阵
		AddMovementInput(Direction,Value);
	}
}

void AMan::TurnAtRate(float Value)
{
	AddControllerYawInput(Value*BaseTurnRate*GetWorld()->DeltaTimeSeconds);
}

void AMan::TurnLookupRate(float Value)
{
	AddControllerPitchInput(Value*BaseLookupRate*GetWorld()->DeltaTimeSeconds);
}

// Called when the game starts or when spawned
void AMan::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMan::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AMan::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMan::MoveRight);
 
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AMan::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AMan::StopJumping);
	
	PlayerInputComponent->BindAxis("CameraYaw", this, &AMan::AddControllerYawInput);
	PlayerInputComponent->BindAxis("CameraPitch", this, &AMan::AddControllerPitchInput);

	PlayerInputComponent->BindAxis("Lookup",this,&AMan::TurnLookupRate);
	PlayerInputComponent->BindAxis("Turn",this,&AMan::TurnAtRate);
}

