// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/BehaviorTreeTask/BTTaskBase.h"
#include "BTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SERVERTESTPROJECT_API UBTTask_Attack : public UBTTaskBase
{
	GENERATED_BODY()
public:
	UBTTask_Attack();

public:
	virtual EBTNodeResult::Type	ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAnimMontage* AttackMontage;
	
};
