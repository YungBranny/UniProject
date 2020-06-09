// Fill out your copyright notice in the Description page of Project Settings.


#include "Npc_CPPAiController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "UObject/ConstructorHelpers.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "BlackBoardKeys.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Character.h"
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
	setupPerceptionSystem ();
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

void ANpc_CPPAiController::onUpdated(TArray<AActor*> const& updatedActors)
{
}

void ANpc_CPPAiController::setupPerceptionSystem()
{
	//creates the ai sense config
	//Creates the sight config
	sight_config = CreateDefaultSubobject<UAISenseConfig_Sight> (TEXT ("Sight Config"));
	//creats the current ai perception component
	SetPerceptionComponent (*CreateDefaultSubobject<UAIPerceptionComponent> (TEXT ("Perception Component")));
	//sets sight and lose sight radius and the angle of vision the ai has
	sight_config->SightRadius = 1000.0f;
	sight_config->LoseSightRadius = sight_config->SightRadius + 100.0f;
	sight_config->PeripheralVisionAngleDegrees = 90.0f;
	//sets how long before the stimulus source dies
	sight_config->SetMaxAge (5.0f);
	//lets the ai see the stimulus source still if its close to the last one it spotted
	sight_config->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	sight_config->DetectionByAffiliation.bDetectEnemies = true;
	sight_config->DetectionByAffiliation.bDetectFriendlies = true;
	sight_config->DetectionByAffiliation.bDetectNeutrals = true;

	//adds the sight configuration to the perception component
	GetPerceptionComponent()->SetDominantSense (*sight_config->GetSenseImplementation ());
//	GetPerceptionComponent ()->OnTargetPerceptionUpdated.AddDynamic (this, &ANpc_CPPAiController::onUpdated);
	GetPerceptionComponent ()->ConfigureSense (*sight_config);
	
}

