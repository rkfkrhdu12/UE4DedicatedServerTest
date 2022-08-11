// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/AnimInstanceBase.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

#include "Monster/MonsterBase.h" ///

// #include "Character/CharacterBase.h"

UAnimInstanceBase::UAnimInstanceBase()
{

}

UAnimInstanceBase::~UAnimInstanceBase()
{

}

void UAnimInstanceBase::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	Character = Cast<ACharacter>(TryGetPawnOwner());
	if (IsValidCharacter())
	{
		SkeletalMesh = Character->GetMesh();
		if (IsValidSkeletalMesh())
		{
			MeshLocationOffsetZ = SkeletalMesh->GetRelativeLocation().Z * -1.f;
		}

		CharacterMovement = Character->GetCharacterMovement();

		DummyArray.Add(Character);

		if (!OnMontageBlendingOut.IsBound())
			OnMontageBlendingOut.AddDynamic(this, &UAnimInstanceBase::OnAnimBlendOut);
		if (!OnPlayMontageNotifyBegin.IsBound())
			OnPlayMontageNotifyBegin.AddDynamic(this, &UAnimInstanceBase::OnAnimNotify);
	}
}

void UAnimInstanceBase::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!IsValidCharacter())
	{
		NativeBeginPlay();
		return;
	}

	DeltaTime = DeltaSeconds;

	UpdateSpeed();
	UpdateDirection();

	UpdateFootIK();
}

void UAnimInstanceBase::UpdateSpeed()
{
	if (!IsValidCharacter()) return;

	MoveSpeed = Character->GetVelocity().Size();
	bIsMoving = MoveSpeed >= 10.f;
}

void UAnimInstanceBase::UpdateDirection()
{
	if (!IsValidCharacter()) return;

	MoveDirection = CalculateDirection(Character->GetVelocity(), Character->GetActorRotation());
}

void UAnimInstanceBase::UpdateIKDisplacement()
{
	FHitResult leftFootHitResult;
	FHitResult rightFootHitResult;

	FootDisplacementCheck(LeftFootSocketName, leftFootHitResult);
	FootDisplacementCheck(RightFootSocketName, rightFootHitResult);

	if (!(leftFootHitResult.bBlockingHit || rightFootHitResult.bBlockingHit)) return;

	float leftFootDistance = leftFootHitResult.Distance;
	float rightFootDistance = rightFootHitResult.Distance;

	float distance = UKismetMathLibrary::SelectFloat(leftFootDistance, rightFootDistance, leftFootDistance >= rightFootDistance);
	distance = (distance - DisplacementOffset) * -1.f;

	Displacement = UKismetMathLibrary::FInterpTo(Displacement, distance, GetDeltaTime(), IKInterpSpeed);
}

void UAnimInstanceBase::UpdateIKGroundDistance(const FName& socketName, FRotator& rotate, float& ik)
{
	FHitResult hitResult;
	FootGroundDistance(socketName, hitResult);
	if (!hitResult.bBlockingHit) return;

	FVector hitNormal = hitResult.Normal;

	float roll = UKismetMathLibrary::DegAtan2(hitNormal.Y, hitNormal.Z);
	float pitch = UKismetMathLibrary::DegAtan2(hitNormal.X, hitNormal.Z) * -1.f;

	FRotator targetRotation = FRotator(pitch, 0.f, roll);

	rotate = UKismetMathLibrary::RInterpTo(rotate, targetRotation, GetDeltaTime(), IKInterpSpeed);

	float target = (hitResult.Distance - (GroundCheckOffset + footToGround)) / -45.f;

	ik = UKismetMathLibrary::FInterpTo(ik, target, GetDeltaTime(), IKInterpSpeed);
}

void UAnimInstanceBase::UpdateFootIK()
{
	if (!IsValidCharacterMovement() || !IsValidCharacter()) return;
	if (CharacterMovement->IsFalling()) return;

	UpdateIKDisplacement();

	UpdateIKGroundDistance(RightFootSocketName, RightFootRotate, RightFootIK);
	UpdateIKGroundDistance(LeftFootSocketName, LeftFootRotate, LeftFootIK);
}


void UAnimInstanceBase::FootDisplacementCheck(const FName& socketName, FHitResult& hitResult)
{
	if (!IsValidSkeletalMesh() || !IsValidCharacter()) return;

	FVector startLocation = GetSocketLocation(socketName);
	startLocation.Z = SkeletalMesh->GetComponentLocation().Z + DisplacementOffset;

	FVector endLocation = startLocation;
	endLocation.Z -= LegLength;

	UKismetSystemLibrary::LineTraceSingle(GetWorld(),
		startLocation, endLocation,
		ETraceTypeQuery::TraceTypeQuery3,
		true,
		DummyArray, EDrawDebugTrace::None, hitResult, true);
}

void UAnimInstanceBase::FootGroundDistance(const FName& socketName, FHitResult& hitResult)
{
	if (!IsValidSkeletalMesh() || !IsValidCharacter()) return;

	FVector socketLocation = GetSocketLocation(socketName);
	FVector startLocation = FVector(socketLocation.X, socketLocation.Y, GetSocketLocation(RootName).Z);
	FVector endLocation = startLocation;
	startLocation.Z += GroundCheckOffset;
	endLocation.Z -= GroundCheckOffset;

	UKismetSystemLibrary::LineTraceSingle(Character->GetWorld(),
		startLocation, endLocation,
		ETraceTypeQuery::TraceTypeQuery3,
		true,
		DummyArray, EDrawDebugTrace::None, hitResult, true);
}

void UAnimInstanceBase::OnAnimBlendOut(UAnimMontage* Montage, bool bInterrupted)
{
	if (!IsValidCharacter()) return;

	// Character->OnAnimBlendOut();
}

void UAnimInstanceBase::OnAnimNotify(FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	if (!IsValidCharacter()) return;

	// Character->OnAnimNotify(NotifyName);
}

FVector UAnimInstanceBase::GetSocketLocation(FName socketName) const
{
	if (!IsValidSkeletalMesh()) return FVector();

	return SkeletalMesh->GetSocketLocation(socketName);
}

float UAnimInstanceBase::GetDeltaTime() const
{
	return GetWorld()->GetDeltaSeconds();
}

/* 변수의 유효함을 검증해주는 함수들입니다. */
#pragma region Variable Valid Functions 

bool UAnimInstanceBase::IsValidCharacter() const
{
#if UE_EDITOR 
	ErrorCheck(!(Character != nullptr && Character->IsValidLowLevelFast()), "Character is Null");
#endif
	return Character != nullptr && Character->IsValidLowLevelFast();
}

bool UAnimInstanceBase::IsValidSkeletalMesh() const
{
#if UE_EDITOR 
	ErrorCheck(!(SkeletalMesh != nullptr && SkeletalMesh->IsValidLowLevelFast()), "SkeletalMesh is Null");
#endif
	return SkeletalMesh != nullptr && SkeletalMesh->IsValidLowLevelFast();
}

bool UAnimInstanceBase::IsValidCharacterMovement() const
{
#if UE_EDITOR 
	ErrorCheck(!(CharacterMovement != nullptr && CharacterMovement->IsValidLowLevelFast()), "CharacterMovement is Null");
#endif
	return CharacterMovement != nullptr && CharacterMovement->IsValidLowLevelFast();
}

void UAnimInstanceBase::ErrorCheck(bool IsLog, const FString ErrorMessage) const
{
#if UE_EDITOR
	if (IsLog)
		UE_LOG(LogTemp, Log, TEXT("%s : %s"), *GetName(), *ErrorMessage);
#endif // UE_EDITOR
}

#pragma endregion
