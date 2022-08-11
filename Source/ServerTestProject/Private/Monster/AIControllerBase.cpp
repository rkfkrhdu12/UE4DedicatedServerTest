// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AIControllerBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Monster/MonsterBase.h"

AAIControllerBase::AAIControllerBase(const FObjectInitializer& ObjectInitializer)
{
	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MonsterCharacter = Cast<AMonsterBase>(InPawn);
	if (MonsterCharacter == nullptr || !MonsterCharacter->IsValidLowLevelFast()) return;

	UBehaviorTree* bt = MonsterCharacter->GetBehaviorTree();
	if (bt == nullptr) return;

	BlackBoardComponent->InitializeBlackboard(*bt->BlackboardAsset);
	KeyID = BlackBoardComponent->GetKeyID("TestActor");
	BehaviorTreeComponent->StartTree(*bt);
}
