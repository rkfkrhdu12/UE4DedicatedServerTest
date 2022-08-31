// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AIControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDetectPawn, AActor*, DetectPawn);

/**
 *
 */
UCLASS()
class SERVERTESTPROJECT_API AAIControllerBase : public AAIController
{
	GENERATED_BODY()
public:
	AAIControllerBase(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION()
		void OnPawnDetected(const TArray<AActor*>& DetectedPawns);
	FOnDetectPawn OnDetectPawnDelegate;

	UFUNCTION()
		void DetectPlayer(AActor* Actor);
protected:
	UPROPERTY(Transient)
		class UBehaviorTreeComponent* BehaviorTreeComponent;

	UPROPERTY(Transient)
		class UBlackboardComponent* BlackBoardComponent;

	UPROPERTY()
		class AMonsterBase* MonsterCharacter;

#pragma region Sight Perception

	class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomVariable_AI)
		float SightRadius = 900.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomVariable_AI)
		float LoseSightRadius = SightRadius + 50.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomVariable_AI)
		float SightAge = 3.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = CustomVariable_AI)
		float SightFOV = 90.f;
#pragma endregion

	class APlayerCharacter* PlayerCharacter;

	int CurState = 0;

	bool bIsFindPlayer = false;
	FName CurStateKeyID;
	FName IsFindPlayerKeyID;
	FName AttackTypeID;
	FName AttackRangeID;
	FName AttackDamageID;

protected:
	bool IsValidBlackBoard() const;

public:
	int GetCurState() const;
	void SetCurState(int val);

	APlayerCharacter* GetPlayerCharacter() const;

	FName GetCurStateKeyID() const { return CurStateKeyID; }
	FName GetIsFindPlayerKeyID() const { return IsFindPlayerKeyID; }
	FName GetAttackTypeID() const { return AttackTypeID; }
	FName GetAttackRangeID() const { return AttackRangeID; }
	FName GetAttackDamageID() const { return AttackDamageID; }
};
