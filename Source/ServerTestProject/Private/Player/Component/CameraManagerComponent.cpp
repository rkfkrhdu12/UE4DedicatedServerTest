// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Component/CameraManagerComponent.h"
#include "Player/PlayerCharacter.h"
#include "Player/Component/InputDataComponent.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

UCameraManagerComponent::UCameraManagerComponent()
{
	PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (!IsValidPlayerCharacter()) return;

	CameraArmComponent = PlayerCharacter->GetCameraArmComponent();
	if (!IsValidCameraArmComponent()) return;
	CameraArmComponent->SetupAttachment(PlayerCharacter->GetRootComponent());
	CameraArmComponent->TargetArmLength = 300.f;

	CameraArmComponent->bInheritPitch = true;
	CameraArmComponent->bInheritYaw = true;
	CameraArmComponent->bInheritRoll = true;

	CameraArmComponent->bEnableCameraLag = true;
	CameraArmComponent->CameraLagSpeed = 10.f;

	CameraArmComponent->bUsePawnControlRotation = true;
	CameraArmComponent->bEnableCameraRotationLag = true;
	CameraArmComponent->CameraRotationLagSpeed = 30.f;

	FVector CameraArmLocation = FVector::ZeroVector;
	CameraArmLocation.X = -4.3f;
	CameraArmLocation.Y = 10.f;
	CameraArmLocation.Z = 40.f;
	FRotator CameraArmRotate = FRotator(340.0f, 0, .0f);
	CameraArmComponent->SetRelativeLocationAndRotation(CameraArmLocation, CameraArmRotate);

	CameraComponent = PlayerCharacter->GetCameraComponent();
	if (!IsValidCameraComponent()) return;
	CameraComponent->SetupAttachment(CameraArmComponent);
	CameraComponent->bUsePawnControlRotation = false;

	InputDataComponent = PlayerCharacter->GetInputDataComponent();
	if (!IsValidInputDataComponent()) return;
}

void UCameraManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	if (!IsValidInputDataComponent()) return;

	// InputDataComponent->OnInputMouseLocationX.AddDynamic(this, &UCameraManagerComponent::Turn);
	// InputDataComponent->OnInputMouseLocationY.AddDynamic(this, &UCameraManagerComponent::LookUp);
}

void UCameraManagerComponent::Turn()
{
	if (!IsValidPlayerCharacter() || !IsValidInputDataComponent()) return;

	PlayerCharacter->AddControllerYawInput(InputDataComponent->GetMouseLocation().X * GetWorld()->GetDeltaSeconds() * 45.f);
}

void UCameraManagerComponent::LookUp()
{
	if (!IsValidPlayerCharacter() || !IsValidCameraArmComponent() || !IsValidInputDataComponent()) return;

	PlayerCharacter->AddControllerPitchInput(InputDataComponent->GetMouseLocation().Y * GetWorld()->GetDeltaSeconds() * 45.f);
}

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool UCameraManagerComponent::IsValidPlayerCharacter() const
{
	return PlayerCharacter != nullptr && PlayerCharacter->IsValidLowLevelFast();
}

bool UCameraManagerComponent::IsValidCameraArmComponent() const
{
	return CameraArmComponent != nullptr && CameraArmComponent->IsValidLowLevelFast();
}

bool UCameraManagerComponent::IsValidCameraComponent() const
{
	return CameraComponent != nullptr && CameraComponent->IsValidLowLevelFast();
}

bool UCameraManagerComponent::IsValidInputDataComponent() const
{
	return InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast();
}

#pragma endregion
