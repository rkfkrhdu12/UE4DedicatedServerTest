//
#include "TestMonster01/State/Monster01BattleState.h"

#include "CoreMinimal.h"
#include "TestMonster01/TestMonster01.h"
#include "TestMonster01/TestMonster01Controller.h"
#include "TestMonster01/TestMonster01BehaviorStateMgr.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Player/PlayerCharacter.h"
#include "Kismet/KismetSystemLibrary.h"

Monster01BattleState::Monster01BattleState(ACharacterBase* OwnerCharacter)
	: StateBase(OwnerCharacter)
{
	Monster = Cast<ATestMonster01>(OwnerCharacter);
	Controller = Cast<ATestMonster01Controller>(Monster->GetController());
}

void Monster01BattleState::Update(float DeltaTime)
{
	if (!IsValidController()) return;

	if (Controller->IsFindPlayer())
	{
		Controller->GetBlackBoardComponent()->SetValueAsVector(Controller->GetMoveLocationID(), GetPlayerLocation());
	}
}

void Monster01BattleState::AnimBlendOut()
{
	if (!IsValidMonster()) return;

	FString str = FString::Printf(TEXT("Monster BattleState AnimBlendOut"));
	UKismetSystemLibrary::PrintString(Monster->GetWorld(), *str);
}

void Monster01BattleState::AnimNotify(class FName notifyName)
{
	if (!IsValidMonster()) return;

	FString str = FString::Printf(TEXT("Monster BattleState AnimNotify"));
	UKismetSystemLibrary::PrintString(Monster->GetWorld(), *str);
}

const FVector Monster01BattleState::GetPlayerLocation() const
{
	if (IsValidController())
		if (Controller->GetPlayerCharacter() != nullptr && Controller->GetPlayerCharacter()->IsValidLowLevelFast())
			return Controller->GetPlayerCharacter()->GetActorLocation();

	return FVector::ZeroVector;
}

bool Monster01BattleState::IsValidMonster() const 
{
	return Monster != nullptr && Monster->IsValidLowLevelFast();
}

bool Monster01BattleState::IsValidController() const
{
#if UE_EDITOR 
	if (IsValidMonster())
		Monster->ErrorCheck(!(Controller != nullptr && Controller->IsValidLowLevelFast()), " Monster01Idle Controller is Null");
#endif
	return Controller != nullptr && Controller->IsValidLowLevelFast();
}
