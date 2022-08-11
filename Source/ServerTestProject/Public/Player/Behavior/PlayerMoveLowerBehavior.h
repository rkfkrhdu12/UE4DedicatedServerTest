#pragma once

#include "Character/Behavior/BehaviorBase.h"

class PlayerMoveLowerBehavior : public BehaviorBase
{
protected:
	class APlayerCharacter* PlayerCharacter = nullptr;

	class UInputDataComponent* InputDataComponent = nullptr;

	class UCameraComponent* CameraComponent = nullptr;
	class USpringArmComponent* CameraArmComponent = nullptr;
	
	float MoveSpeed = .75f;

	FVector MoveDirection = FVector::ZeroVector;

public:
	PlayerMoveLowerBehavior(class ACharacterBase* OwnerCharacer);

	void Update(float DeltaTime) override;

private:
	bool IsValidPlayerCharacter() const;
	bool IsValidCameraComponent() const;
	bool IsValidCameraArmComponent() const;
	bool IsValidInputDataComponent() const;
};

