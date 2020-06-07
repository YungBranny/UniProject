// Fill out your copyright notice in the Description page of Project Settings.


#include "NPCDefaultAi.h"

// Sets default values
ANPCDefaultAi::ANPCDefaultAi()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCDefaultAi::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCDefaultAi::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ANPCDefaultAi::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

