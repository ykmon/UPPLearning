// Fill out your copyright notice in the Description page of Project Settings.


#include "MyMovementComponent.h"

//#include <ocidl.h>
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"
#include "winioctl.h"
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

void UMyMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    // 确保所有事物持续有效，以便进行移动。
	if (!PawnOwner||!UpdatedComponent||ShouldSkipUpdate(DeltaTime))
	{
		return;
	}
	
	// 获取（然后清除）ACreature::Tick中设置的移动向量
	FVector DeltaMovement// 运动向量
	=ConsumeInputVector().GetClampedToMaxSize(1)*DeltaTime*150;

	if (!DeltaMovement.IsNearlyZero())// 运动向量非0
	{
		FHitResult HitResult;
		SafeMoveUpdatedComponent(DeltaMovement,UpdatedComponent->GetComponentRotation(),true,HitResult);
        // 若发生碰撞，尝试滑过去
		if (HitResult.IsValidBlockingHit())
		{
			SlideAlongSurface(DeltaMovement,1.f-HitResult.Time,HitResult.Normal,HitResult);
		}
	}
};
