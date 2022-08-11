// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CameraManagerComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SERVERTESTPROJECT_API UCameraManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UCameraManagerComponent();
protected:
	virtual void BeginPlay() override;

public:
	void Turn();
	void LookUp();

protected:
	class APlayerCharacter* PlayerCharacter;
	class UInputDataComponent* InputDataComponent;

	class USpringArmComponent* CameraArmComponent;
	class UCameraComponent* CameraComponent;

	FVector MousePosition = FVector::ZeroVector;
public:
	bool IsValidPlayerCharacter() const;
	bool IsValidCameraArmComponent() const;
	bool IsValidCameraComponent() const;
	bool IsValidInputDataComponent() const;
};
