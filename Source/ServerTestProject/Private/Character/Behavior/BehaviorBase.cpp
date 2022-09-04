
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

void BehaviorBase::AnimBlendOut()
{

}

void BehaviorBase::AnimNotify(FName notifyName)
{

}
