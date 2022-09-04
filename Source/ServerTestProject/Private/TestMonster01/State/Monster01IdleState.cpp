//
#include "TestMonster01/State/Monster01IdleState.h"

#include "CoreMinimal.h"
#include "TestMonster01/TestMonster01.h"
#include "TestMonster01/TestMonster01Controller.h"
#include "TestMonster01/TestMonster01BehaviorStateMgr.h"

Monster01IdleState::Monster01IdleState(ACharacterBase* OwnerCharacter)
	:StateBase(OwnerCharacter)
{
	Monster = Cast<ATestMonster01>(OwnerCharacter);
	Controller = Cast<ATestMonster01Controller>(Monster->GetController());
}

void Monster01IdleState::Update(float DeltaTime)
{
	if (!IsValidMonster() || !IsValidController()) return;

	if (Controller->IsFindPlayer())
		Monster->ChangeState(static_cast<uint8>(EMonster01State::Battle));
}

bool Monster01IdleState::IsValidMonster() const
{
	return Monster != nullptr && Monster->IsValidLowLevelFast();
}

bool Monster01IdleState::IsValidController() const
{
#if UE_EDITOR 
	if(IsValidMonster())
		Monster->ErrorCheck(!(Controller != nullptr && Controller->IsValidLowLevelFast()), " Monster01Idle Controller is Null");
#endif
	return Controller != nullptr && Controller->IsValidLowLevelFast();
}
