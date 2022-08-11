#include "Player/Behavior/PlayerMoveLowerBehavior.h"
#include "Player/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/Component/InputDataComponent.h"

PlayerMoveLowerBehavior::PlayerMoveLowerBehavior(ACharacterBase* OwnerCharacter)
	: BehaviorBase(OwnerCharacter)
{
	PlayerCharacter = static_cast<APlayerCharacter*>(OwnerCharacter);
	if (!IsValidPlayerCharacter()) return;

	InputDataComponent = PlayerCharacter->GetInputDataComponent();
	if (!IsValidInputDataComponent()) return;

	CameraComponent = PlayerCharacter->GetCameraComponent();
	if (!IsValidCameraComponent()) return;

	CameraArmComponent = PlayerCharacter->GetCameraArmComponent();
	if (!IsValidCameraArmComponent()) return;
}

void PlayerMoveLowerBehavior::Update(float DeltaTime)
{
	if (!IsValidPlayerCharacter() || !IsValidCameraComponent() || !IsValidInputDataComponent()) return;

	MoveDirection = InputDataComponent->GetMoveDirection();

	Character->AddMovementInput(CameraComponent->GetForwardVector(), MoveDirection.X * MoveSpeed);
	Character->AddMovementInput(CameraComponent->GetRightVector(), MoveDirection.Y * MoveSpeed);
}

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool PlayerMoveLowerBehavior::IsValidPlayerCharacter() const
{
	return PlayerCharacter != nullptr && PlayerCharacter->IsValidLowLevelFast();
}

bool PlayerMoveLowerBehavior::IsValidCameraComponent() const
{
#if UE_EDITOR 
	if (!IsValidPlayerCharacter()) return false;
	PlayerCharacter->ErrorCheck(!(CameraComponent != nullptr && CameraComponent->IsValidLowLevelFast()), "PlayerMoveLowerBehavior : CameraComponent is Null");
#endif
	return CameraComponent != nullptr && CameraComponent->IsValidLowLevelFast();
}

bool PlayerMoveLowerBehavior::IsValidCameraArmComponent() const
{
#if UE_EDITOR 
	if (!IsValidPlayerCharacter()) return false;
	PlayerCharacter->ErrorCheck(!(CameraArmComponent != nullptr && CameraArmComponent->IsValidLowLevelFast()), "PlayerMoveLowerBehavior : CameraArmComponent is Null");
#endif
	return CameraArmComponent != nullptr && CameraArmComponent->IsValidLowLevelFast();
}

bool PlayerMoveLowerBehavior::IsValidInputDataComponent() const
{
#if UE_EDITOR 
	if (!IsValidPlayerCharacter()) return false;
	PlayerCharacter->ErrorCheck(!(InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast()), "PlayerMoveLowerBehavior : InputDataComponent is Null");
#endif
	return InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast();
}

#pragma endregion