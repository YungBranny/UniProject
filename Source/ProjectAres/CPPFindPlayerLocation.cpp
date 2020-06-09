// Fill out your copyright notice in the Description page of Project Settings.


#include "CPPFindPlayerLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "Npc_CPPAiController.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "BlackBoardKeys.h"


UCPPFindPlayerLocation::UCPPFindPlayerLocation(FObjectInitializer const& ObjectInitializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UCPPFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//get the player character and the npc controller
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter (GetWorld (), 0);
	auto const controller = Cast<ANpc_CPPAiController> (OwnerComp.GetAIOwner ());
	
	//gets the player location
	FVector const player_location = player->GetActorLocation ();
	if (randomSearch)
	{
		FNavLocation Location;
		//gets the navigation system and generates a random location near to the player
		UNavigationSystemV1* const nav_system = UNavigationSystemV1::GetCurrent (( GetWorld () ));
		if (nav_system->GetRandomPointInNavigableRadius(player_location,searchRadius,Location,nullptr))
		{
			controller->get_blackboard()->SetValueAsVector (bb_keys::target_location, Location.Location);
		}
	}
	else
	{
		controller->get_blackboard()->SetValueAsVector (bb_keys::target_location, player_location);
	}

	//Finishes the task with success
	FinishLatentTask (OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
