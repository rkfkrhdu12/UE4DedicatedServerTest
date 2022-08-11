
class StateBase
{
public:
	StateBase(class ACharacterBase* OwnerCharacter);
	virtual ~StateBase();

public:
	virtual void Start();
	virtual void Update(float DeltaTime);

protected:
	ACharacterBase* Character = nullptr;

	uint8 UpperBehavior = static_cast<uint8>(0);
	uint8 LowerBehavior = static_cast<uint8>(0);
protected:
	bool IsValidCharacter() const;

public:
	const uint8 GetUpperIndex() const;
	const uint8 GetLowerIndex() const;
};