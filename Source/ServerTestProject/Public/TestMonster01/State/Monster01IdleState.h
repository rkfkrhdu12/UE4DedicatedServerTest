#pragma once

#include "Character/State/StateBase.h"

class Monster01IdleState : public StateBase
{
private:
	class ATestMonster01* Monster;
public:
	Monster01IdleState(class ACharacterBase* OwnerCharacter);

	virtual void Update(float DeltaTime) override;
};

