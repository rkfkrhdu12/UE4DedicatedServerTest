// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/CharacterBase.h"
#include "MonsterBase.generated.h"

/**
 *
 */
UCLASS()
class SERVERTESTPROJECT_API AMonsterBase : public ACharacterBase
{
	GENERATED_BODY()
public:
	AMonsterBase();
	virtual ~AMonsterBase();

public:
	virtual void BeginPlay() override;

public:
	virtual void ChangeState(const uint8& nextState) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = AI)
		class UBehaviorTree* BehaviorTree;

public:
	class UBehaviorTree* GetBehaviorTree() const { return BehaviorTree; }
	void SetBehaviorTree(class UBehaviorTree* val) { BehaviorTree = val; }
};
