// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AnimInstanceBase.generated.h"

/**
 *
 */
UCLASS()
class SERVERTESTPROJECT_API UAnimInstanceBase : public UAnimInstance
{
	GENERATED_BODY()
public:
	UAnimInstanceBase();
	virtual ~UAnimInstanceBase();
public:
	virtual void NativeBeginPlay() override;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
private:
	void UpdateSpeed();
	void UpdateDirection();

	void UpdateIKDisplacement();
	void UpdateIKGroundDistance(const FName& socketName, FRotator& rotate, float& ik);
	void UpdateFootIK();

	void FootDisplacementCheck(const FName& socketName, FHitResult& hitResult);
	void FootGroundDistance(const FName& socketName, FHitResult& hitResult);

public:
	UFUNCTION()
		virtual void OnAnimBlendOut(UAnimMontage* Montage, bool bInterrupted);
	UFUNCTION()
		virtual void OnAnimNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

public:
	FVector GetSocketLocation(FName socketName) const;

	float GetDeltaTime() const;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class ACharacter* Character = nullptr;

	class USkeletalMeshComponent* SkeletalMesh = nullptr;
	class UCharacterMovementComponent* CharacterMovement = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsMoving = false;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bIsFalling = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MoveSpeed = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float MoveDirection = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float AimPitchOffset = 0.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float AimYawOffset = 0.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float Displacement = 0.0f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator RightFootRotate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		FRotator LeftFootRotate;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float RightFootIK;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		float LeftFootIK;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (AnimNotifyBoneName = "true"))
		FName RootName = "root";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (AnimNotifyBoneName = "true"))
		FName LeftFootSocketName = "IK_Foot_L";
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), meta = (AnimNotifyBoneName = "true"))
		FName RightFootSocketName = "IK_Foot_R";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float IKInterpSpeed = 15.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float DisplacementOffset = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float GroundCheckOffset = 60.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float LegLength = 80.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float footToGround = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
		float MeshLocationOffsetZ = 90.f;
	float DeltaTime = 0.0f;

	TArray<AActor*> DummyArray;

protected:
	bool IsValidCharacter() const;
	bool IsValidSkeletalMesh() const;
	bool IsValidCharacterMovement() const;

	void ErrorCheck(bool IsLog, const FString ErrorMessage) const;
};
