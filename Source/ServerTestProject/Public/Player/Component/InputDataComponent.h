// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputDataComponent.generated.h"

UENUM(BlueprintType)
enum class EInputKey : uint8
{
	MoveForward 	UMETA(DisplayName = "MoveForward"),
	MoveRight 		UMETA(DisplayName = "MoveRight"),

	Aiming 			UMETA(DisplayName = "Aiming"),
	Shooting 		UMETA(DisplayName = "Shooting"),
	Last
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SERVERTESTPROJECT_API UInputDataComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInputDataComponent();

protected:
	FVector MouseLocation = FVector::ZeroVector;
	FVector MoveDirection = FVector::ZeroVector;

	bool bIsAim = false;
	bool bIsShoot = false;
public:
	FVector GetMouseLocation() const;
	void SetMouseLocationX(float AxisValue);
	void SetMouseLocationY(float AxisValue);

	FVector GetMoveDirection() const;
	void SetMoveDirectionX(float AxisValue);
	void SetMoveDirectionY(float AxisValue);

	void IsAim(bool param1);
	bool IsAim() const;
	void IsShoot(bool param1);
	bool IsShoot() const;
	void Setup(UInputComponent* PlayerInputComponent);

};
