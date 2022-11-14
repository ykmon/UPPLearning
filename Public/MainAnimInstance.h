// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "MainAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPPBEGIN_API UMainAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Movement)
	float MovementSpeed;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Movement)
	bool IsJumping;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category = Movement)
	class APawn* Pawn;// 获得主角的信息

	virtual  void NativeInitializeAnimation() override;// 初始化动画参数

	UFUNCTION(BlueprintCallable,Category = AnimationProperty)
	void UpdateAnimationProperties();
};
