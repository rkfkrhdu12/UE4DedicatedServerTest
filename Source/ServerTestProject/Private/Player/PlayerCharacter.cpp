// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerCharacter.h"
#include "Player/Component/CameraManagerComponent.h"
#include "Player/Component/InputDataComponent.h"
#include "Character/AnimInstanceBase.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Player/PlayerBehaviorStateManager.h"

APlayerCharacter::APlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	// Component Init
	InputDataComponent = CreateDefaultSubobject<UInputDataComponent>(TEXT("InputData"));
	CameraArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	// Manager Init
	CamareManager = CreateDefaultSubobject<UCameraManagerComponent>(TEXT("CamaraManager"));
	StateManager = CreateDefaultSubobject<UPlayerBehaviorStateManager>(TEXT("BehaviorStateManager"));
}

APlayerCharacter::~APlayerCharacter()
{

}

/* 입력 데이터 델리게이트 바인딩 함수들입니다. */
#pragma region InputData Binding Functions 

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!IsValidInputDataComponent()) return;

	InputDataComponent->Setup(PlayerInputComponent);
}

void APlayerCharacter::MouseLeftPress()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->IsShoot(true);
}

void APlayerCharacter::MouseLeftRelease()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->IsShoot(false);
}

void APlayerCharacter::MouseRightPress()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->IsAim(true);
}

void APlayerCharacter::MouseRightRelease()
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->IsAim(false);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMoveDirectionX(AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	if (!IsValidInputDataComponent()) return;

	InputDataComponent->SetMoveDirectionY(AxisValue);
}

void APlayerCharacter::Turn(float AxisValue)
{
	if (!IsValidInputDataComponent() || !IsvalidCameraManager()) return;

	InputDataComponent->SetMouseLocationX(AxisValue);
	CamareManager->Turn();
}

void APlayerCharacter::LookUp(float AxisValue)
{
	if (!IsValidInputDataComponent() || !IsvalidCameraManager()) return;

	InputDataComponent->SetMouseLocationY(AxisValue);
	CamareManager->LookUp();
}

#pragma endregion

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool APlayerCharacter::IsValidInputDataComponent() const
{
#if UE_EDITOR 
	ErrorCheck(!(InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast()), "InputDataComponent is Null");
#endif
	return InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast();
}

bool APlayerCharacter::IsvalidCameraManager() const
{
#if UE_EDITOR 
	ErrorCheck(!(CamareManager != nullptr && CamareManager->IsValidLowLevelFast()), "CamareManager is Null");
#endif
	return CamareManager != nullptr && CamareManager->IsValidLowLevelFast();
}

#pragma endregion


//void APlayerCharacter::Shoot()
//{
//	if (Projectile == nullptr || !Projectile->IsValidLowLevelFast() ||
//		Mesh == nullptr || !Mesh->IsValidLowLevelFast()) return;
//
//	FActorSpawnParameters SpawnParams;
//	SpawnParams.Owner = this;
//
//	GetWorld()->SpawnActor<AActor>(Projectile, Mesh->GetSocketLocation(GunMuzzleName), GetBaseAimRotation(), SpawnParams);
//}