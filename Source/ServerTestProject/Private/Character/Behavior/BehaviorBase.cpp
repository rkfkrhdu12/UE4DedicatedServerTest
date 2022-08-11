
#include "Character\Behavior\BehaviorBase.h"


BehaviorBase::BehaviorBase(ACharacterBase* OwnerCharacer)
{
	Character = OwnerCharacer;
}

BehaviorBase::~BehaviorBase()
{

}

void BehaviorBase::Update(float DeltaTime)
{

}