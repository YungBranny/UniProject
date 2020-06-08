// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Npc_CPPAiController.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTARES_API ANpc_CPPAiController : public AAIController
{
	GENERATED_BODY()
public:
	ANpc_CPPAiController (FObjectInitializer const& object_initializer = FObjectInitializer::Get ());
	void BeginPlay () override;
	void OnPossess(APawn* pawn) override;
	class UBlackboardComponent* get_blackboard() const;

private:
	UPROPERTY (EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = ( AllowPrivateAccess = "true" ))
	class UBehaviorTreeComponent* behavior_tree_component;

	UPROPERTY (EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = ( AllowPrivateAccess = "true" ))
	class UBehaviorTree* behavior_tree;

	class UBlackboardComponent* blackboard;
	
};
