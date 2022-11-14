// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "MyMovementComponent.generated.h"


/**
 * 
 */
UCLASS()
class CPPBEGIN_API UMyMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
	
public:
	//继承自PawnMovementComponent类，需重写TickComponent方法
	virtual  void TickComponent(float DeltaTime, enum ELevelTick, FActorComponentTickFunction* ThisTickFunction) override;
};
