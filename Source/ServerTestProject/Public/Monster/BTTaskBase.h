// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskBase.generated.h"

/**
 * 
 */
UCLASS()
class SERVERTESTPROJECT_API UBTTaskBase : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTaskBase(const FObjectInitializer& ObjectInitailizer);

	virtual void OnGameplayTaskActivated(UGameplayTask& Task) override;
	virtual EBTNodeResult::Type	ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	const class UBlackboardComponent* BlackBoard;
	class AAIControllerBase* Controller;
	class AMonsterBase* Monster;

protected:
	bool IsValidBlackBoard() const;
	bool IsValidController() const;
	bool IsValidCharacter() const;
};
