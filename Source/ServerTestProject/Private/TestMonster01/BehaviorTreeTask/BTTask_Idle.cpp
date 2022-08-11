// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster01/BehaviorTreeTask/BTTask_Idle.h"

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	if (!UBTTaskBase::ExecuteTask(OwnerComp, NodeMemory)) return EBTNodeResult::Failed;

	FTimerHandle WaitHandle;
	float WaitTime = 3.f;
	

	return EBTNodeResult::Succeeded;
}
