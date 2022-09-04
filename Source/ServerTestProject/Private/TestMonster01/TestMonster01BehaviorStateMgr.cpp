// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster01/TestMonster01BehaviorStateMgr.h"
#include "Kismet/KismetSystemLibrary.h"

#include "TestMonster01/State/Monster01IdleState.h"
#include "TestMonster01/State/Monster01BattleState.h"

void UTestMonster01BehaviorStateMgr::BeginPlay()
{
	Super::BeginPlay();

	RegisterState(new Monster01IdleState(Character), static_cast<uint8>(EMonster01State::Idle));
	RegisterState(new Monster01BattleState(Character), static_cast<uint8>(EMonster01State::Battle));
}
