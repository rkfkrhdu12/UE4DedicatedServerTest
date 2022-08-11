// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/AnimInstanceBase.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SERVERTESTPROJECT_API UPlayerAnimInstance : public UAnimInstanceBase
{
	GENERATED_BODY()
public:
	UPlayerAnimInstance();
	virtual ~UPlayerAnimInstance();
public:
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	void UpdateAimRotate();
protected:
	class UInputDataComponent* InputDataComponent = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool bIsAiming = false; 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float RootYawOffset = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator MoveRotation = FRotator::ZeroRotator;
	FRotator PrevMoveRotation;
private:
	bool IsValidInputDataComponent() const;
};
 