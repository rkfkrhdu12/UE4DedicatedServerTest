// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerBehaviorStateManager.h"

#include "Player/Behavior/PlayerMoveLowerBehavior.h"

#include "Player/State/PlayerIdleState.h"
#include "Kismet/KismetSystemLibrary.h"

UPlayerBehaviorStateManager::UPlayerBehaviorStateManager() : UBehaviorStateManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

UPlayerBehaviorStateManager::~UPlayerBehaviorStateManager()
{
	return;
	/// ////////////////////////////////////////////////
	//for (uint8 i = static_cast<uint8>(EPlayerBehavior::Idle); i != static_cast<uint8>(EPlayerBehavior::Last); ++i)
	//{
	//	BehaviorBase* deleteData = nullptr;
	//	if (UpperBehaviorList.Find(i))
	//	{
	//		deleteData = UpperBehaviorList[i];
	//		if (deleteData != nullptr)
	//		{
	//			UpperBehaviorList.Remove(i);
	//			delete deleteData;
	//			deleteData = nullptr;
	//		}
	//	}

	//	if (LowerBehaviorList.Find(i))
	//	{
	//		deleteData = LowerBehaviorList[i];
	//		if (deleteData != nullptr)
	//		{
	//			LowerBehaviorList.Remove(i);
	//			delete deleteData;
	//			deleteData = nullptr;
	//		}
	//	}
	//}

	//for (uint8 i = static_cast<uint8>(EPlayerState::Idle); i != static_cast<uint8>(EPlayerState::Last); ++i)
	//{
	//	StateBase* deleteData = nullptr;
	//	if (StateList.Find(i))
	//	{
	//		deleteData = StateList[i];
	//		if (deleteData != nullptr)
	//		{
	//			StateList.Remove(i);
	//			delete deleteData;
	//			deleteData = nullptr;
	//		}
	//	}
	//}
}

void UPlayerBehaviorStateManager::BeginPlay()
{
	Super::BeginPlay();

	RegisterLowerBehavior(new PlayerMoveLowerBehavior(Character), static_cast<uint8>(EPlayerBehavior::Idle));

	RegisterState(new PlayerIdleState(Character), static_cast<uint8>(EPlayerState::Idle));
}
