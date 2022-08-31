// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster01/TestMonster01Controller.h"
#include "Monster/MonsterBase.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"

ATestMonster01Controller::ATestMonster01Controller(const FObjectInitializer& ObjectInitializer)
	:AAIControllerBase(ObjectInitializer)
{
}

ATestMonster01Controller::~ATestMonster01Controller()
{

}

void ATestMonster01Controller::BeginPlay()
{
	Super::BeginPlay();
}

void ATestMonster01Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
