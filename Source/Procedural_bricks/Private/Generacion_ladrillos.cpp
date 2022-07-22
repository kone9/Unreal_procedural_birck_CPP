// Fill out your copyright notice in the Description page of Project Settings.


#include "Generacion_ladrillos.h"
#include <Engine/World.h>

// Sets default values
AGeneracion_ladrillos::AGeneracion_ladrillos()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	timeToSpawn = 1.0f;

	amount_x = 10;
	amount_z = 10;
	brick_position = FVector::ZeroVector;
	count_x = 0;
	count_z = 0;

	distace_spawn_x = 300;
	distace_spawn_z = 200;
}

// Called when the game starts or when spawned
void AGeneracion_ladrillos::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() == nullptr) return;
	GetWorld()->GetTimerManager().SetTimer(timer_spawn_handler, this, &AGeneracion_ladrillos::SpawnTimer_out, timeToSpawn, true);
	
	spawn_brick(brick_reference, brick_position);//spawn new brick first
	
}

void AGeneracion_ladrillos::SpawnTimer_out()
{
	bool can_instance_brick = check_brick_amoutn_end();
	if (can_instance_brick)
	{
		spawn_brick(brick_reference, brick_position);//spawn new brick
	}
}





void AGeneracion_ladrillos::spawn_brick(TSubclassOf<AActor> brick, FVector positionBrick)
{
	if (GetWorld() == nullptr) return;
	
	//distance spawn
	positionBrick.X = distace_spawn_x * count_x;
	positionBrick.Z = distace_spawn_z * count_z;

	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AActor>(
		brick,
		GetActorLocation() + positionBrick,
		GetActorRotation(),
		SpawnParams
		);
	
}

bool AGeneracion_ladrillos::check_brick_amoutn_end()
{
	//if (GEngine)
	//	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Blue, TEXT("instance brick"));

	if (count_x > amount_x)//if there are more in X than quantity X
	{
		count_x = 0;
		count_z += 1;
		if (count_z > amount_z)//if there are more in Y than quantity Y
		{
			GetWorld()->GetTimerManager().ClearTimer(timer_spawn_handler);//stop timer
			return false;
		}
	}
	else
	{
		count_x += 1;
	}
	return true;
}


// Called every frame
void AGeneracion_ladrillos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

