// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc_CPPAiController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"

#include "ProjectAres.h"

ANpc_CPPAiController::ANpc_CPPAiController(FObjectInitializer const& object_initializer)
{

	static ConstructorHelpers::FObjectFinder <UBehaviorTree> obj (TEXT ("BehaviorTree'/Game/Ai/CPP_NPC/NPC_CPPBT.NPC_CPPBT'"));
	if(obj.Succeeded())
	{
		behavior_tree = obj.Object;
	}
	
	behavior_tree_component = object_initializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT ("BehaviorComp"));
	blackboard = object_initializer.CreateDefaultSubobject<UBlackboardComponent> (this, TEXT ("BlackboadComp"));
}

void ANpc_CPPAiController::BeginPlay()
{
	Super::BeginPlay ();
	RunBehaviorTree (behavior_tree);
	behavior_tree_component->StartTree (*behavior_tree);
}

void ANpc_CPPAiController::OnPossess(APawn* pawn)
{
	Super::OnPossess (pawn);
	if (blackboard)
	{
		blackboard->InitializeBlackboard (*behavior_tree->BlackboardAsset);
	}
}

UBlackboardComponent* ANpc_CPPAiController::get_blackboard() const
{
	return blackboard;
}

