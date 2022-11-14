// Fill out your copyright notice in the Description page of Project Settings.


#include "Creature.h"

#include "MyMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UObject/ConstructorHelpers.h"

#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"
#include "winioctl.h"
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

// Sets default values
ACreature::ACreature()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//初始化球形网格体，并将其设置为根组件
	SphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	SphereComp->SetSphereRadius(80);
	SphereComp->SetCollisionProfileName(TEXT("BlockAll")); // 设置碰撞特性
	SphereComp->SetHiddenInGame(false); // 在游戏中不隐藏
	SetRootComponent(SphereComp);

	//初始化静态网格体，并将静态网格体的默认值设置为MeshComponentAsset
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	MeshComponent->SetupAttachment(GetRootComponent()); // MeshComponent bind to RootComponent
	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshComponentAsset(
		TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));// 去资源文件夹下查找一个资源并加载
	if (MeshComponentAsset.Succeeded())
	{
		MeshComponent->SetStaticMesh(MeshComponentAsset.Object);
		MeshComponent->SetRelativeLocation(FVector(0.f, 0, -50));
	}

	//初始化弹簧臂网格体，将其附着在根组件上，并设置默认的臂长，延迟系数等参数
	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 400.f;
	SpringArmComp->SetRelativeRotation(FRotator(-45.f, 0, 0));
	SpringArmComp->bEnableCameraLag = true;
	SpringArmComp->CameraLagSpeed = 3;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); // Create a Camera
	Camera->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	// 把摄像机绑定到弹簧臂的插槽里，如果没有USpringArmComponent::SocketName，就会绑定到模型原点
	// Camera->SetAttachment(GetRootComponent());
	// Camera->SetRelativeLocation(FVector(-300.f, 0, 300));
	// Camera->SetRelativeRotation(FRotator(-45.f, 0, 0));

	AutoPossessPlayer = EAutoReceiveInput::Player0; // 让0号玩家拥有这个角色

	MovementComponent = CreateDefaultSubobject<UMyMovementComponent>(TEXT("MovementComponent"));
	MovementComponent->UpdatedComponent = RootComponent;

	CameraInput = FVector2d(0.f,0);
}

// Called when the game starts or when spawned
void ACreature::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACreature::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
#if 0
	FVector NewLocation = GetActorLocation() + CurrentVelocity * DeltaTime;
	SetActorLocation(NewLocation);
#endif
	// 左右旋转控制的是小球的旋转 
	FRotator NewRotation = GetActorRotation();
	NewRotation.Yaw += CameraInput.X;
	SetActorRotation(NewRotation);
	// 上下俯仰头是控制的弹簧臂的俯仰
	FRotator NewSpringArmRotation = SpringArmComp->GetComponentRotation();
	NewSpringArmRotation.Pitch += CameraInput.Y;
	NewSpringArmRotation.Pitch = FMath::Clamp(NewSpringArmRotation.Pitch,-80.f,-15.f);// 限制弹簧臂俯仰的角度
	SpringArmComp->SetWorldRotation(NewSpringArmRotation);
}

// Called to bind functionality to input
void ACreature::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// 绑定输入
	PlayerInputComponent->BindAxis("MoveForward", this, &ACreature::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACreature::MoveRight);
	PlayerInputComponent->BindAxis("CameraPitch",this,&ACreature::CameraPitch);
	PlayerInputComponent->BindAxis("CameraYaw",this,&ACreature::CameraYaw);
}

void ACreature::CameraPitch(float Value)
{
	CameraInput.Y = Value;
}

void ACreature::CameraYaw(float Value)
{
	CameraInput.X = Value;
}

UPawnMovementComponent* ACreature::GetMovementComponent() const
{
	return MovementComponent;
}

void ACreature::MoveForward(float Value)
{
	
	if (MovementComponent)
	{
		MovementComponent->AddInputVector(GetActorForwardVector()*Value);
	}
}

void ACreature::MoveRight(float Value)
{
	//CurrentVelocity.Y = FMath::Clamp(Value, -1.f, 1.f) * MaxSpeed;
	//AddMovementInput(GetActorRightVector()*Value);
	if (MovementComponent)
	{
		MovementComponent->AddInputVector(GetActorRightVector()*Value);
	}
}
