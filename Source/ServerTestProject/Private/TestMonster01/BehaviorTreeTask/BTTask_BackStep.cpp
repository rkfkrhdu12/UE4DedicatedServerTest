// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster01/BehaviorTreeTask/BTTask_BackStep.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"
#include "Monster/AIControllerBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Monster/MonsterBase.h"


UBTTask_BackStep::UBTTask_BackStep()
{

}

EBTNodeResult::Type UBTTask_BackStep::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (IsValidController() && IsValidBlackBoard() && IsValidCharacter())
	{
		FVector PlayerLocation, MonsterLocation, MoveLocation;
		float MoveDelta = 0;
		//while (MoveDelta > 1000)
		{
			PlayerLocation = Controller->GetPlayerCharacter()->GetActorLocation();
			MonsterLocation = MonsterCharacter->GetActorLocation();

			MoveLocation = -UKismetMathLibrary::GetForwardVector(UKismetMathLibrary::FindLookAtRotation(MonsterLocation, PlayerLocation));

			MoveDelta += MoveLocation.Size();
			Controller->MoveToLocation(MonsterLocation + MoveLocation * 250);
		}
	}

	return EBTNodeResult::Succeeded;
}
