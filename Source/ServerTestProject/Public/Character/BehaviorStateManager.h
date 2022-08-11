// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BehaviorStateManager.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SERVERTESTPROJECT_API UBehaviorStateManager : public UActorComponent
{
	GENERATED_BODY()
public:	
	UBehaviorStateManager();
	~UBehaviorStateManager();

protected:
	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void RegisterState(class StateBase* StateClass, const uint8 StateIndex);
	void RegisterUpperBehavior(class BehaviorBase* StateClass, const uint8 BehaviorIndex);
	void RegisterLowerBehavior(class BehaviorBase* StateClass, const uint8 BehaviorIndex);

	void ChangeState(const uint8& nextState);
	void ReturnState();

protected:
	class ACharacterBase* Character = nullptr;

	TMap<const uint8, class StateBase*> StateList;
	TMap<const uint8, class BehaviorBase*> UpperBehaviorList;
	TMap<const uint8, class BehaviorBase*> LowerBehaviorList;

	uint8 CurState = static_cast<uint8>(0);
	uint8 PrevState = static_cast<uint8>(99);

	uint8 CurUpperBehavior = static_cast<uint8>(0);
	uint8 CurLowerBehavior = static_cast<uint8>(0);
	uint8 PrevUpperBehavior = static_cast<uint8>(99);
	uint8 PrevLowerBehavior = static_cast<uint8>(99);

protected:
	bool IsValidCharacter() const;
};
