// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/AIControllerBase.h"
#include "TestMonster01Controller.generated.h"

/**
 *
 */
UCLASS()
class SERVERTESTPROJECT_API ATestMonster01Controller : public AAIControllerBase
{
	GENERATED_BODY()
public:
	ATestMonster01Controller(const FObjectInitializer& ObjectInitializer);
	~ATestMonster01Controller();
public:
	virtual	void BeginPlay() override;

	virtual void OnPossess(APawn* InPawn) override;

protected:

public:
};
