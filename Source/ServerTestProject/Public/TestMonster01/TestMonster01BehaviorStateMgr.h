// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BehaviorStateManager.h"
#include "TestMonster01BehaviorStateMgr.generated.h"

UENUM(BlueprintType)
enum class EMonster01Behavior : uint8
{
	Idle,
	Battle,
	Last
};

UENUM(BlueprintType)
enum class EMonster01State : uint8
{
	Idle,
	Battle,
	Last
};

/**
 * 
 */
UCLASS()
class SERVERTESTPROJECT_API UTestMonster01BehaviorStateMgr : public UBehaviorStateManager
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
};
