// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloorSwitch.generated.h"

UCLASS()
class CPPBEGIN_API AFloorSwitch : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloorSwitch();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	class UBoxComponent* TriggerBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* FloorSwitch;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* Door;

	UPROPERTY(BlueprintReadWrite)
	FVector InitialDoorLocation;

	UPROPERTY(BlueprintReadWrite)
	FVector InitialSwitchLocation;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	                    int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(BlueprintImplementableEvent)// 蓝图实现，所以不在C++当中定义，而是在蓝图中定义
	void RaiseDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void LowerDoor();

	UFUNCTION(BlueprintImplementableEvent)
	void RaiseFloorSwitch();

	UFUNCTION(BlueprintImplementableEvent)
	void LowerFloorSwitch();

	UFUNCTION(BlueprintCallable)
	void UpdateSwitchLocation(float Z);

	UFUNCTION(BlueprintCallable)
	void UpdateDoorLocation(float Z);
	
};
