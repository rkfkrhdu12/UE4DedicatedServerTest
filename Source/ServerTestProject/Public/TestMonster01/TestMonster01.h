// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Monster/MonsterBase.h"
#include "TestMonster01.generated.h"

/**
 * 
 */
UCLASS()
class SERVERTESTPROJECT_API ATestMonster01 : public AMonsterBase
{
	GENERATED_BODY()
public:
	ATestMonster01();
	virtual ~ATestMonster01();
	
protected:
	class UCharacterMovementComponent* CharacterMovement;

private:
	bool IsValidCharacterMovement() const;

};
