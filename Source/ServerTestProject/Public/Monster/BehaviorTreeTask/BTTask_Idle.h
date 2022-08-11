// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BTTaskBase.h"
#include "BTTask_Idle.generated.h"

/**
 * 
 */
UCLASS()
class SERVERTESTPROJECT_API UBTTask_Idle : public UBTTaskBase
{
	GENERATED_BODY()
public:
	UBTTask_Idle(const FObjectInitializer& ObjectInitailizer);

public:
	virtual EBTNodeResult::Type	ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
