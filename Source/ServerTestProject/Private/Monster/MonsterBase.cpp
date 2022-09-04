// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/MonsterBase.h"
#include "BehaviorTree/BehaviorTree.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionComponent.h"
#include "Monster/AIControllerBase.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/PlayerCharacter.h"

AMonsterBase::AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

AMonsterBase::~AMonsterBase()
{

}

void AMonsterBase::BeginPlay()
{
	Super::BeginPlay();
}

void AMonsterBase::ChangeState(const uint8& nextState)
{
	ACharacterBase::ChangeState(nextState);
}
