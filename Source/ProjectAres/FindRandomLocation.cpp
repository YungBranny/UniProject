// Fill out your copyright notice in the Description page of Project Settings.


#include "FindRandomLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Npc_CPPAiController.h"
//#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BlackBoardKeys.h"


UFindRandomLocation::UFindRandomLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT ("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get the ai controller and the NPC its controlling 
	auto const controller = Cast <ANpc_CPPAiController> (OwnerComp.GetAIOwner());
	auto const npc = controller->GetPawn ();

	//Gets the npcs origin location
	FVector const origin = npc->GetActorLocation ();
	FNavLocation location;

	//Gets the navigation sytem and generates a random location on the Nav Mesh
	UNavigationSystemV1* const nav_system = UNavigationSystemV1::GetCurrent (GetWorld ());
	if (nav_system->GetRandomPointInNavigableRadius(origin,searchRadius,location,nullptr))
	{
		controller->get_blackboard ()->SetValueAsVector (bb_keys::target_location, location.Location);
	}

	//Finishes the task with success
	FinishLatentTask (OwnerComp, EBTNodeResult::Succeeded);
	
	return EBTNodeResult::Succeeded;
	
	
}
