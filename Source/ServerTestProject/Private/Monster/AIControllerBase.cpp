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
	MoveLocationID = "MoveLocation";
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

	MonsterCharacter->OnChangeStateDelegate.AddDynamic(this, &AAIControllerBase::UpdateState);
	UpdateState();
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

	bIsFindPlayer = !IsFindPlayer();

	if (IsValidBlackBoard())
		BlackBoardComponent->SetValueAsBool(GetIsFindPlayerKeyID(), IsFindPlayer());
}

void AAIControllerBase::UpdateState()
{
	if (IsValidBlackBoard())
	{
		BlackBoardComponent->SetValueAsInt(GetCurStateKeyID(), GetCurState());

		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%d"), GetCurState()));
	}
}

bool AAIControllerBase::IsValidBlackBoard() const
{
#if UE_EDITOR 
	if (IsValidMonster())
		MonsterCharacter->ErrorCheck(!(BlackBoardComponent != nullptr && BlackBoardComponent->IsValidLowLevelFast()), " Controller's BlackBoardComponent is Null");
#endif
	return BlackBoardComponent != nullptr && BlackBoardComponent->IsValidLowLevelFast();
}

bool AAIControllerBase::IsValidMonster() const
{
	return MonsterCharacter != nullptr && MonsterCharacter->IsValidLowLevelFast();
}

int AAIControllerBase::GetCurState() const
{
	if (IsValidMonster())
		return MonsterCharacter->GetCurState();

	return 0;
}

void AAIControllerBase::SetCurState(int val)
{
	if (IsValidMonster())
		MonsterCharacter->ChangeState(static_cast<uint8>(val));

	if (IsValidBlackBoard())
	{
		BlackBoardComponent->SetValueAsInt(GetCurStateKeyID(), GetCurState());

		UKismetSystemLibrary::PrintString(GetWorld(), FString::Printf(TEXT("%d"), GetCurState()));
	}
}

APlayerCharacter* AAIControllerBase::GetPlayerCharacter() const
{
	return PlayerCharacter;
}
