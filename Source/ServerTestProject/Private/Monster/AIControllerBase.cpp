// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AIControllerBase.h"
#include "Monster/MonsterBase.h"
#include "Player/PlayerCharacter.h"

#include "Kismet/KismetSystemLibrary.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"

AAIControllerBase::AAIControllerBase(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	BehaviorTreeComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComponent"));
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));

	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception")));

	SightConfig->SightRadius = SightRadius;
	SightConfig->LoseSightRadius = LoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = SightFOV;
	SightConfig->SetMaxAge(SightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AAIControllerBase::OnPawnDetected);

	CurStateKeyID = "CurState";
	IsFindPlayerKeyID = "IsFindPlayer";
	AttackTypeID = "AttackType";
	AttackRangeID = "AttackRange";
	AttackDamageID = "AttackDamage";
}

void AAIControllerBase::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	MonsterCharacter = Cast<AMonsterBase>(InPawn);
	if (MonsterCharacter == nullptr || !MonsterCharacter->IsValidLowLevelFast()) return;

	UBehaviorTree* bt = MonsterCharacter->GetBehaviorTree();
	if (bt == nullptr) return;

	BlackBoardComponent->InitializeBlackboard(*bt->BlackboardAsset);
	BehaviorTreeComponent->StartTree(*bt);

	OnDetectPawnDelegate.AddDynamic(this, &AAIControllerBase::DetectPlayer);
}

void AAIControllerBase::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{
	for (auto var : DetectedPawns)
	{
		if (var == nullptr || !var->IsValidLowLevelFast()) continue;

		if (OnDetectPawnDelegate.IsBound())
			OnDetectPawnDelegate.Broadcast(var);
	}
}

void AAIControllerBase::DetectPlayer(AActor* Actor)
{
	if (!Cast<APlayerCharacter>(Actor)) return;

	if (PlayerCharacter == nullptr) PlayerCharacter = Cast<APlayerCharacter>(Actor);

	bIsFindPlayer = !bIsFindPlayer;

	if (IsValidBlackBoard())
		BlackBoardComponent->SetValueAsBool(GetIsFindPlayerKeyID(), bIsFindPlayer);
}

bool AAIControllerBase::IsValidBlackBoard() const
{
	return BlackBoardComponent != nullptr && BlackBoardComponent->IsValidLowLevelFast();
}

int AAIControllerBase::GetCurState() const
{
	return CurState;
}

void AAIControllerBase::SetCurState(int val)
{
	CurState = val;

	if (IsValidBlackBoard())
		BlackBoardComponent->SetValueAsInt(GetCurStateKeyID(), CurState);
}

APlayerCharacter* AAIControllerBase::GetPlayerCharacter() const
{
	return PlayerCharacter;
}
