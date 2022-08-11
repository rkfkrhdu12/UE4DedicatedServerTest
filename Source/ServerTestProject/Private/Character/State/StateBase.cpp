
#include "Character\State\StateBase.h"
#include "Character/CharacterBase.h"
#include "Player/PlayerBehaviorStateManager.h"

StateBase::StateBase(class ACharacterBase* OwnerCharacter)
{
	Character = OwnerCharacter;
	if (!IsValidCharacter()) return;

	UpperBehavior = static_cast<uint8>(EPlayerBehavior::Idle);
	LowerBehavior = static_cast<uint8>(EPlayerBehavior::Idle);
}

StateBase::~StateBase()
{

}

void StateBase::Start()
{

}

void StateBase::Update(float DeltaTime)
{

}

bool StateBase::IsValidCharacter() const
{
	return Character != nullptr && Character->IsValidLowLevelFast();
}

const uint8 StateBase::GetUpperIndex() const
{
	return UpperBehavior;
}

const uint8 StateBase::GetLowerIndex() const
{
	return LowerBehavior;
}
