// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Man.generated.h"

UCLASS()
class CPPBEGIN_API AMan : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMan();
	// 弹簧臂组件
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Camera)
	class USpringArmComponent* SpringArmComp;
	// 摄像头组件
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = Camera)
	class UCameraComponent* Camera;

	float BaseTurnRate;// 旋转率
	float BaseLookupRate;
	void MoveForward(float Value);
	void MoveRight(float Value);// 上下左右平移
	void TurnAtRate(float Value);
	void TurnLookupRate(float Value);// 上下左右旋转
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
