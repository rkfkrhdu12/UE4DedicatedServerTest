#include "TestMonster01/State/Monster01IdleState.h"

#include "CoreMinimal.h"
#include "TestMonster01/TestMonster01.h"

Monster01IdleState::Monster01IdleState(ACharacterBase* OwnerCharacter)
	:StateBase(OwnerCharacter)
{
	Monster = Cast<ATestMonster01>(OwnerCharacter);
}

void Monster01IdleState::Update(float DeltaTime)
{
	if (!Monster->IsValidLowLevelFast()) return;


}
