// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Creature.generated.h"

UCLASS()
class CPPBEGIN_API ACreature : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ACreature();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(EditAnywhere)
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere)
	float MaxSpeed;

	UPROPERTY(VisibleAnywhere)
	class USphereComponent* SphereComp;// 球形组件

	UPROPERTY(VisibleAnywhere)
	class USpringArmComponent* SpringArmComp;// 弹簧臂组件

	UPROPERTY(VisibleAnywhere)
	class UMyMovementComponent* MovementComponent;
	
	virtual UPawnMovementComponent* GetMovementComponent() const override;
	
private:
	void MoveForward(float Value);
	void MoveRight(float Value);

	void CameraPitch(float Value);// 抬头低头
	void CameraYaw(float Value);// 转头
	FVector2d CameraInput;// 距离当前视角变化量
};
