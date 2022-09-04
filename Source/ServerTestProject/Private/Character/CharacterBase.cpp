
#include "Character/CharacterBase.h"
#include "Character/BehaviorStateManager.h"

#include "Kismet/KismetSystemLibrary.h"
#include "GameFramework/Actor.h"

#include "Net/UnrealNetwork.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
}

void ACharacterBase::OnAnimBlendOutA(UAnimMontage* Montage, bool bInterrupted)
{
	if (OnAnimBlendOutDelegate.IsBound())
		OnAnimBlendOutDelegate.Broadcast();
}

void ACharacterBase::OnAnimNotifyA(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (OnAnimNotifyDelegate.IsBound())
		OnAnimNotifyDelegate.Broadcast(NotifyName);
}

void ACharacterBase::ChangeState(const uint8& nextState)
{
	if (!IsValidStateMgr()) return;

	StateManager->ChangeState(nextState);
	if (OnChangeStateDelegate.IsBound())
		OnChangeStateDelegate.Broadcast();
}

void ACharacterBase::ReturnState()
{
	if (!IsValidStateMgr()) return;

	StateManager->ReturnState();
	if (OnChangeStateDelegate.IsBound())
		OnChangeStateDelegate.Broadcast();
}

uint8 ACharacterBase::GetCurState() const
{
	if (IsValidStateMgr())
		return StateManager->GetCurState();
	
	return 0U;
}

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool ACharacterBase::IsValidStateMgr() const
{
#if UE_EDITOR 
	ErrorCheck(!(StateManager != nullptr && StateManager->IsValidLowLevelFast()), "StateManager is Null");
#endif
	return StateManager != nullptr && StateManager->IsValidLowLevelFast();
}

void ACharacterBase::ErrorCheck(bool IsLog, const FString ErrorMessage) const
{
#if UE_EDITOR
	if (IsLog)
		UE_LOG(LogTemp, Log, TEXT("%s : %s"), *GetName(), *ErrorMessage);
#endif // UE_EDITOR
}

#pragma endregion