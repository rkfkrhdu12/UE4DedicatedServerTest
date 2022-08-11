// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMonster01/TestMonster01.h"
#include "GameFramework/CharacterMovementComponent.h"

ATestMonster01::ATestMonster01()
	: AMonsterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	CharacterMovement = GetCharacterMovement();
	if (!IsValidCharacterMovement()) return;

	CharacterMovement->bOrientRotationToMovement = true;
	CharacterMovement->RotationRate = FRotator(0.f, 600.f, 0.f);
}

ATestMonster01::~ATestMonster01()
{

}

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool ATestMonster01::IsValidCharacterMovement() const
{
#if UE_EDITOR 
	ErrorCheck(!(CharacterMovement != nullptr && CharacterMovement->IsValidLowLevelFast()), "CharacterMovement is Null");
#endif
	return CharacterMovement != nullptr && CharacterMovement->IsValidLowLevelFast();
}

#pragma endregion