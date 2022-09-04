// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/BehaviorStateManager.h"
#include "Character/CharacterBase.h"
#include "Character/State/StateBase.h"
#include "Character/Behavior/BehaviorBase.h"

UBehaviorStateManager::UBehaviorStateManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UBehaviorStateManager::~UBehaviorStateManager()
{
	for (uint8 i = 0U; (UpperBehaviorList.Num() || LowerBehaviorList.Num()); ++i)
	{
		BehaviorBase* deleteData = nullptr;
		if (UpperBehaviorList.Find(i))
		{
			deleteData = UpperBehaviorList[i];
			if (deleteData != nullptr)
			{
				UpperBehaviorList.Remove(i);
				delete deleteData;
				deleteData = nullptr;
			}
		}

		if (LowerBehaviorList.Find(i))
		{
			deleteData = LowerBehaviorList[i];
			if (deleteData != nullptr)
			{
				LowerBehaviorList.Remove(i);
				delete deleteData;
				deleteData = nullptr;
			}
		}
	}

	for (uint8 i = 0U; StateList.Num(); ++i)
	{
		StateBase* deleteData = nullptr;
		if (StateList.Find(i))
		{
			deleteData = StateList[i];
			if (deleteData != nullptr)
			{
				StateList.Remove(i);
				delete deleteData;
				deleteData = nullptr;
			}
		}
	}
}

// Called when the game starts
void UBehaviorStateManager::BeginPlay()
{
	Super::BeginPlay();

	Character = Cast<ACharacterBase>(GetOwner());
}

void UBehaviorStateManager::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!StateList.Find(GetCurState())) return;
	if (StateList[GetCurState()] == nullptr) return;

	auto CurStateClass = StateList[CurState];

	CurStateClass->Update(DeltaTime);
	 
	if (UpperBehaviorList.Find(CurStateClass->GetUpperIndex()))
		UpperBehaviorList[CurStateClass->GetUpperIndex()]->Update(DeltaTime);

	if (LowerBehaviorList.Find(CurStateClass->GetUpperIndex()))
		LowerBehaviorList[CurStateClass->GetUpperIndex()]->Update(DeltaTime);
}

void UBehaviorStateManager::RegisterState(StateBase* StateClass, const uint8 StateIndex)
{
	if (StateClass == nullptr) return;

	StateList.Add(StateIndex, StateClass);
}

void UBehaviorStateManager::RegisterUpperBehavior(BehaviorBase* StateClass, const uint8 BehaviorIndex)
{
	if (StateClass == nullptr) return;
	if (UpperBehaviorList.Find(BehaviorIndex)) return;

	UpperBehaviorList.Add(BehaviorIndex, StateClass);
}

void UBehaviorStateManager::RegisterLowerBehavior(BehaviorBase* StateClass, const uint8 BehaviorIndex)
{
	if (StateClass == nullptr) return;
	if (LowerBehaviorList.Find(BehaviorIndex)) return;

	LowerBehaviorList.Add(BehaviorIndex, StateClass);
}

void UBehaviorStateManager::ChangeState(const uint8& nextState)
{
	if (nextState == CurState) return;

	PrevState = CurState;
	CurState = nextState;

	if (!StateList.Find(CurState)) return;

	// Update State
	StateList[CurState]->Start();
}

void UBehaviorStateManager::ReturnState()
{
	if (static_cast<uint8>(99) == PrevState) ChangeState(static_cast<uint8>(0));

	CurState = PrevState;
	PrevState = static_cast<uint8>(99);

	if (!StateList.Find(CurState)) return;

	// Update State
	StateList[CurState]->Start();
}

uint8 UBehaviorStateManager::GetCurState() const
{
	return CurState;
}

bool UBehaviorStateManager::IsValidCharacter() const
{
	return Character != nullptr && Character->IsValidLowLevelFast();
}

