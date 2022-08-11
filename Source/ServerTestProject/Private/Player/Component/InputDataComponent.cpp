// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Component/InputDataComponent.h"
#include "Player/PlayerCharacter.h"
#include "Components/InputComponent.h"

// Sets default values for this component's properties
UInputDataComponent::UInputDataComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

FVector UInputDataComponent::GetMouseLocation() const
{
	return MouseLocation;
}

void UInputDataComponent::SetMouseLocationY(float AxisValue)
{
	MouseLocation.Y = AxisValue;
}

void UInputDataComponent::SetMouseLocationX(float AxisValue)
{
	MouseLocation.X = AxisValue;
}

void UInputDataComponent::SetMoveDirectionY(float AxisValue)
{
	MoveDirection.Y = AxisValue;
}

FVector UInputDataComponent::GetMoveDirection() const
{
	return MoveDirection;
}

void UInputDataComponent::SetMoveDirectionX(float AxisValue)
{
	MoveDirection.X = AxisValue;
}

void UInputDataComponent::IsAim(bool param1)
{
	bIsAim = param1;
}

bool UInputDataComponent::IsAim() const
{
	return bIsAim;
}

void UInputDataComponent::IsShoot(bool param1)
{
	bIsShoot = param1;
}

bool UInputDataComponent::IsShoot() const
{
	return bIsShoot;
}

void UInputDataComponent::Setup(UInputComponent* InputComponent)
{
	check(InputComponent);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(GetOwner());
	if (PlayerCharacter == nullptr || !PlayerCharacter->IsValidLowLevelFast()) return;

	InputComponent->BindAxis("MoveForward", PlayerCharacter, &APlayerCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", PlayerCharacter, &APlayerCharacter::MoveRight);

	InputComponent->BindAxis("Turn", PlayerCharacter, &APlayerCharacter::Turn);
	InputComponent->BindAxis("LookUp", PlayerCharacter, &APlayerCharacter::LookUp);

	InputComponent->BindAction("Fire", IE_Pressed, PlayerCharacter, &APlayerCharacter::MouseLeftPress);
	InputComponent->BindAction("Fire", IE_Released, PlayerCharacter, &APlayerCharacter::MouseLeftRelease);
	InputComponent->BindAction("Fire2", IE_Pressed, PlayerCharacter, &APlayerCharacter::MouseRightPress);
	InputComponent->BindAction("Fire2", IE_Released, PlayerCharacter, &APlayerCharacter::MouseRightRelease);
}
