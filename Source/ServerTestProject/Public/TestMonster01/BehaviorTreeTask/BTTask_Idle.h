// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BehaviorTreeTask/BTTaskBase.h"
#include "BTTask_Idle.generated.h"

/**
 * 
 */
UCLASS()
class SERVERTESTPROJECT_API UBTTask_Idle : public UBTTaskBase
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type	ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	// UPROPERTY(Edit)
};
