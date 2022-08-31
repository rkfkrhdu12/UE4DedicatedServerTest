// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/PlayerBehaviorStateManager.h"

#include "Player/Behavior/PlayerMoveLowerBehavior.h"

#include "Player/State/PlayerIdleState.h"
#include "Kismet/KismetSystemLibrary.h"

UPlayerBehaviorStateManager::UPlayerBehaviorStateManager() : UBehaviorStateManager()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerBehaviorStateManager::BeginPlay()
{
	Super::BeginPlay();

	RegisterLowerBehavior(new PlayerMoveLowerBehavior(Character), static_cast<uint8>(EPlayerBehavior::Idle));

	RegisterState(new PlayerIdleState(Character), static_cast<uint8>(EPlayerState::Idle));
}
