// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BehaviorTreeTask/BTTask_Idle.h"

UBTTask_Idle::UBTTask_Idle(const FObjectInitializer& ObjectInitailizer)
	: UBTTaskBase(ObjectInitailizer)
{
	NodeName = "Idle Behavior";
}

EBTNodeResult::Type UBTTask_Idle::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (!IsValidBlackBoard() || !IsValidController() || !IsValidCharacter()) return EBTNodeResult::Failed;



	return EBTNodeResult::Succeeded;
}
