// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterBase.h"
#include "BehaviorTree/BehaviorTree.h"

AMonsterBase::AMonsterBase()
	: ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

AMonsterBase::~AMonsterBase()
{
	
}
