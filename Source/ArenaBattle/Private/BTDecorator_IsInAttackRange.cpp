// Fill out your copyright notice in the Description page of Project Settings.


#include "BTDecorator_IsInAttackRange.h"
#include "ABAIController.h"
#include "ABCharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTDecorator_IsInAttackRange::UBTDecorator_IsInAttackRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_IsInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	//auto ContollingPawn = OwnerComp.GetAIOwner()->GetPawn();
	auto ContollingPawn = Cast<AABCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (nullptr == ContollingPawn)
	{
		return false;
	}

	auto Target = Cast<AABCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AABAIController::TargetKey));

	if (nullptr == Target)
	{
		return false;
	}

	//bResult = (Target->GetDistanceTo(ContollingPawn) <= 200.0f);
	bResult = (Target->GetDistanceTo(ContollingPawn) <= ContollingPawn->GetFinalAttackRange());

	return bResult;
}
