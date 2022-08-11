
#include "Character/CharacterBase.h"
#include "Character/BehaviorStateManager.h"

#include "Kismet/KismetSystemLibrary.h"


ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;
}

ACharacterBase::~ACharacterBase()
{

}

void ACharacterBase::OnAnimBlendOutA(UAnimMontage* Montage, bool bInterrupted)
{
	OnAnimBlendOutDelegate.Broadcast();
}

void ACharacterBase::OnAnimNotifyA(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	OnAnimNotifyDelegate.Broadcast(NotifyName);
}

void ACharacterBase::ChangeState(const uint8& nextState)
{
	if (StateManager == nullptr || !StateManager->IsValidLowLevelFast()) return;

	StateManager->ChangeState(nextState);
	OnChangeStateDelegate.Broadcast();
}

void ACharacterBase::ReturnState()
{
	if (StateManager == nullptr || !StateManager->IsValidLowLevelFast()) return;

	StateManager->ReturnState();
	OnChangeStateDelegate.Broadcast();
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