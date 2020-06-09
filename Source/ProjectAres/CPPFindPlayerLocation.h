// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "CPPFindPlayerLocation.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class PROJECTARES_API UCPPFindPlayerLocation : public UBTTask_BlackboardBase
{
	
	GENERATED_BODY()
public:
	UCPPFindPlayerLocation (FObjectInitializer const& ObjectInitializer);
	
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
protected:
	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = "Search", meta = ( AllowProtectedAccess = "true" ))
		bool randomSearch = false;
	
	UPROPERTY (EditAnywhere, BlueprintReadWrite, Category = "Search", meta = ( AllowProtectedAccess = "true" ))
		float searchRadius = 150.0f;
};
