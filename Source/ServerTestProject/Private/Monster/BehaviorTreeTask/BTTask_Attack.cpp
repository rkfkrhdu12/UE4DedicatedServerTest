// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BehaviorTreeTask/BTTask_Attack.h"
#include "Monster/MonsterBase.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTask_Attack::UBTTask_Attack()
{
	bCreateNodeInstance = true;
	NodeName = "Attack";
}

EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (IsValidCharacter())
	{
		FTimerHandle WaitHandle;
		float AnimTime = MonsterCharacter->PlayAnimMontage(AttackMontage);

	}

	return EBTNodeResult::InProgress;
}
