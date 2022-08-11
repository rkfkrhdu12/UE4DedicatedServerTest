// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCharacterEvent);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnAnimBlendOut);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAnimNotify, const FName&, NotifyName);

UCLASS()
class SERVERTESTPROJECT_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();
	virtual ~ACharacterBase();
public:
	FOnCharacterEvent OnChangeStateDelegate;

	FOnAnimBlendOut OnAnimBlendOutDelegate;
	FOnAnimNotify OnAnimNotifyDelegate;

	UFUNCTION()
		virtual void OnAnimBlendOutA(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		virtual void OnAnimNotifyA(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	virtual void OnAnimBlendOut() {}
	virtual void OnAnimNotify(FName NotifyName) {}
public:
	void ChangeState(const uint8& nextState);
	void ReturnState();

protected:
	class UBehaviorStateManager* StateManager = nullptr;

	uint8 CurState = static_cast<uint8>(0);

protected:
	bool IsValidStateMgr() const;

public:
	void ErrorCheck(bool IsLog, const FString ErrorMessage) const;
};
