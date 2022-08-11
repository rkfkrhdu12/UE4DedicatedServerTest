// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerAnimInstance.h"
#include "Player/PlayerCharacter.h"
#include "Player/Component/InputDataComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{

}

UPlayerAnimInstance::~UPlayerAnimInstance()
{

}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	if (!IsValidCharacter()) return;

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Character);
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsValidLowLevelFast()) return;

	InputDataComponent = PlayerCharacter->GetInputDataComponent();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	UpdateAimRotate();
}

void UPlayerAnimInstance::UpdateAimRotate()
{
	if (!IsValidInputDataComponent()) return;

	bIsAiming = InputDataComponent->IsAim();

	if (!IsValidCharacter()) return;

	FRotator AimRotate = Character->GetBaseAimRotation();
	float pitch = AimRotate.Pitch;

	AimPitchOffset = (pitch >= 180) ?
		pitch - 360.f :
		pitch;

	PrevMoveRotation = MoveRotation;
	MoveRotation = Character->GetActorRotation();

	if (MoveSpeed > 0.f || bIsFalling)
	{
		AimYawOffset = 0.f;
		RootYawOffset = UKismetMathLibrary::FInterpTo(RootYawOffset, 0.0f, DeltaTime, 20.f);
	}
	else
	{
		RootYawOffset = static_cast<int>(RootYawOffset - UKismetMathLibrary::NormalizedDeltaRotator(MoveRotation, PrevMoveRotation).Yaw) % 360;
		AimYawOffset = -RootYawOffset;
	}
}

bool UPlayerAnimInstance::IsValidInputDataComponent() const
{
#if UE_EDITOR 
	ErrorCheck(!(InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast()), "InputDataComponent is Null");
#endif
	return InputDataComponent != nullptr && InputDataComponent->IsValidLowLevelFast();
}
