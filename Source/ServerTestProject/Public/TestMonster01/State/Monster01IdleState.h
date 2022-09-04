#pragma once

#include "Character/State/StateBase.h"

class Monster01IdleState : public StateBase
{
protected:
	class ATestMonster01* Monster;
	class ATestMonster01Controller* Controller;
public:
	Monster01IdleState(class ACharacterBase* OwnerCharacter);

	virtual void Update(float DeltaTime) override;

private:
	bool IsValidMonster() const;
	bool IsValidController() const;
};

