// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Floater.generated.h"

UCLASS()
class CPPBEGIN_API AFloater : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloater();
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category = "ActorMeshComponents")
	UStaticMeshComponent* StaticMesh;

	// 场景中（实例化）可编辑，蓝图可读写
	UPROPERTY(EditInstanceOnly,BlueprintReadWrite,Category = "Floater Variables")
	FVector InitialLocation;// = FVector(0);

	// 蓝图窗口可编辑，蓝图可读写
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category = "Floater Variables")
	bool bInitializeFloaterLocation;

	// 场景中（实例化）可编辑，蓝图可读写
	UPROPERTY(VisibleInstanceOnly,BlueprintReadWrite,Category = "Floater Variables")
	FVector PlacedLocation;

	// 蓝图窗口可见，蓝图窗口可读写
	UPROPERTY(VisibleDefaultsOnly,BlueprintReadWrite,Category = "Floater Variables")
	FVector WorldOrigin;
	
	// 任意窗口可编辑，蓝图只读
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Floater Variables")
	FVector InitialDirection;

	// 任意窗口可编辑，蓝图只读
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = "Floater Variables")
	bool bShouldFloat;

	UPROPERTY(EditAnywhere,Category = "Floater Variables")
	bool bIsLocal;// 是否使用局部坐标系

	UPROPERTY(EditAnywhere,Category = "Floater Variables")
	FRotator InitialRotator;

	UPROPERTY(EditAnywhere,Category = "Floater Variables")
	FVector InitialForce;// 初始力

	UPROPERTY(EditAnywhere,Category = "Floater Variables")
	FVector InitialTorque;// 初始扭矩

	UPROPERTY(EditAnywhere,Category = "Floater Variables")
	float A;

	UPROPERTY(EditAnywhere,Category = "Floater Variables")
	float B;
private:
	float RunningTime;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
