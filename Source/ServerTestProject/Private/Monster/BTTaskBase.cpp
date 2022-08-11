// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/BTTaskBase.h"
#include "Monster/AIControllerBase.h"
#include "Monster/MonsterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetSystemLibrary.h"

UBTTaskBase::UBTTaskBase(const FObjectInitializer& ObjectInitailizer)
{
	bCreateNodeInstance = true;
	NodeName = "NullTask";
}

void UBTTaskBase::OnGameplayTaskActivated(UGameplayTask& Task)
{
	Super::OnGameplayTaskActivated(Task);

	UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("OnGameplayTaskActivated")));
}

EBTNodeResult::Type UBTTaskBase::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	BlackBoard = OwnerComp.GetBlackboardComponent();
	Controller = Cast<AAIControllerBase>(OwnerComp.GetAIOwner());
	if (BlackBoard == nullptr || Controller == nullptr) return EBTNodeResult::Failed;

	Monster = Cast<AMonsterBase>(Controller->GetPawn());
	if (Monster == nullptr) return EBTNodeResult::Failed;

	return EBTNodeResult::Succeeded;
}

bool UBTTaskBase::IsValidBlackBoard() const
{
	return BlackBoard != nullptr && BlackBoard->IsValidLowLevelFast();
}

bool UBTTaskBase::IsValidController() const
{
	return Controller != nullptr && Controller->IsValidLowLevelFast();
}

bool UBTTaskBase::IsValidCharacter() const
{
	return Monster != nullptr && Monster->IsValidLowLevelFast();
}
