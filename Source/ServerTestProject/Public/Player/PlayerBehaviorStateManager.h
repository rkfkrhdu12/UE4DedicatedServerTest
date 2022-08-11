// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/BehaviorStateManager.h"
#include "PlayerBehaviorStateManager.generated.h"

UENUM(BlueprintType)
enum class EPlayerBehavior : uint8
{
	Idle,
	Last
};

UENUM(BlueprintType)
enum class EPlayerState : uint8
{
	Idle,
	Last
};

UCLASS()
class SERVERTESTPROJECT_API UPlayerBehaviorStateManager : public UBehaviorStateManager
{
	GENERATED_BODY()
public:
	UPlayerBehaviorStateManager();
	~UPlayerBehaviorStateManager();

protected:
	virtual void BeginPlay() override;
};
