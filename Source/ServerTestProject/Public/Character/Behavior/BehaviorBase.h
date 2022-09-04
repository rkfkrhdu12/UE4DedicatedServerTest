
class BehaviorBase
{
public:
	BehaviorBase(class ACharacterBase* OwnerCharacer);
	virtual ~BehaviorBase();

public:
	virtual void Update(float DeltaTime);

	virtual void AnimBlendOut();
	virtual void AnimNotify(class FName notifyName);

protected:
	class ACharacterBase* Character;
};