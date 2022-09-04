#pragma once

#include "Character/State/StateBase.h"
 #include "Math/Vector.h"

class Monster01BattleState : public StateBase
{
protected:
	class ATestMonster01* Monster;
	class ATestMonster01Controller* Controller;

public:
	Monster01BattleState(class ACharacterBase* OwnerCharacter);

	virtual void Update(float DeltaTime) override;
	
	virtual void AnimBlendOut() override;
	virtual void AnimNotify(class FName notifyName) override;
public:
	const FVector GetPlayerLocation() const;

private:
	bool IsValidMonster() const;
	bool IsValidController() const;
};