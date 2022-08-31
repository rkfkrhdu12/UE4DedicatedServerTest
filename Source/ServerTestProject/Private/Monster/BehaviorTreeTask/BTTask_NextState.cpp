// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BehaviorTreeTask/BTTask_NextState.h"
#include "Monster/AIControllerBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Int.h"

UBTTask_NextState::UBTTask_NextState()
{
	NodeName = "NextState";
}

EBTNodeResult::Type UBTTask_NextState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (IsValidController() && IsValidBlackBoard())
	{
		Controller->SetCurState(NextState);
		BlackBoard->SetValue<UBlackboardKeyType_Int>(Controller->GetCurStateKeyID(), NextState);
	}

	return EBTNodeResult::Succeeded;
}
