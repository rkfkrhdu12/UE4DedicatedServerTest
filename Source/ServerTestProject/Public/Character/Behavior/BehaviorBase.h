
class BehaviorBase
{
public:
	BehaviorBase(class ACharacterBase* OwnerCharacer);
	virtual ~BehaviorBase();

public:
	virtual void Update(float DeltaTime);

protected:
	class ACharacterBase* Character;
};