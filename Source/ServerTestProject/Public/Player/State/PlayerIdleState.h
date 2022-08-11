#pragma once
#include "Character/State/StateBase.h"

class PlayerIdleState : public StateBase
{
public:
	PlayerIdleState(class ACharacterBase* OwnerCharacter);
};
