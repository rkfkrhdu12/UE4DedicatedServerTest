// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BehaviorTreeTask/BTTask_MoveForAttack.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Float.h"
#include "Player/PlayerCharacter.h"
#include "Monster/AIControllerBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monster/MonsterBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"

UBTTask_MoveForAttack::UBTTask_MoveForAttack()
{
	NodeName = "MoveForAttack";
}

EBTNodeResult::Type UBTTask_MoveForAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (IsValidController() && IsValidBlackBoard() && IsValidCharacter())
	{
		float AttackRange = BlackBoard->GetValue<UBlackboardKeyType_Float>(Controller->GetAttackRangeID());

		FVector PlayerLocation = Controller->GetPlayerCharacter()->GetActorLocation();

		BlackBoard->SetValue<UBlackboardKeyType_Vector>(Controller->GetMoveLocationID(), PlayerLocation);
// 
// 		FVector MonsterLocation = MonsterCharacter->GetActorLocation();
// 
// 		FVector MoveLocation = UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(MonsterLocation, PlayerLocation));
// 
// 		FVector Destination = MonsterLocation + MoveLocation * 100;
// 
// 		Controller->MoveToLocation(PlayerLocation);
// 
// 		while (UKismetMathLibrary::Vector_Distance(MonsterLocation, PlayerLocation) > 150)
// 		{
// 			return EBTNodeResult::Succeeded;
// 			// Destination);
// 		}
	}

	return EBTNodeResult::Succeeded;
}
