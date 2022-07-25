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
	count_x = 0;
	count_z = 0;

	distace_spawn_x = 300;
	distace_spawn_z = 200;

	lineal_can_instantiate_bricks = true;

}

// Called when the game starts or when spawned
void AGeneracion_ladrillos::BeginPlay()
{
	Super::BeginPlay();

	if (GetWorld() == nullptr) return;

	if (lineal_can_instantiate_bricks || vertical_can_instantiate_bricks)
	{
		FVector initi_brick_position = FVector::ZeroVector;
		spawn_brick(brick_reference, initi_brick_position);//spawn new brick first
	
		GetWorld()->GetTimerManager().SetTimer(timer_spawn_handler, this, &AGeneracion_ladrillos::SpawnTimer_out, timeToSpawn, true);
	}
	
	
}



void AGeneracion_ladrillos::SpawnTimer_out()
{
	bool can_instance_brick = check_brick_amoutn_end();
	if (can_instance_brick)
	{
		if (lineal_can_instantiate_bricks)//if instance lineal
		{
			FVector new_linealbrick_position = lineal_check_position();
			spawn_brick(brick_reference, new_linealbrick_position);//spawn new brick
		}
		if (vertical_can_instantiate_bricks)//if instance vertical
		{
			FVector new_vertical_brick_position = vertical_check_position();
			spawn_brick(brick_reference, new_vertical_brick_position);//spawn new brick
		}
	}
}


void AGeneracion_ladrillos::spawn_brick(TSubclassOf<AActor> brick, FVector positionBrick)
{
	if (GetWorld() == nullptr) return;
	FActorSpawnParameters SpawnParams;
	
	AActor* newbrick = GetWorld()->SpawnActor<AActor>(
		brick,
		positionBrick,
		FRotator::ZeroRotator,
		SpawnParams
		);
	
	FAttachmentTransformRules rules(
			EAttachmentRule::KeepRelative,
			EAttachmentRule::KeepRelative,
			EAttachmentRule::KeepRelative,
			false
		);

	newbrick->AttachToActor(this, rules);

	
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

//distance spawn lineal
FVector AGeneracion_ladrillos::lineal_check_position()
{
	FVector brick_position = FVector::ZeroVector;
	brick_position.X = GetActorLocation().X + (distace_spawn_x * count_x);
	brick_position.Y = 0;
	brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);
	return brick_position;
}

//distance spawn vertical
FVector AGeneracion_ladrillos::vertical_check_position()
{
	FVector brick_position = FVector::ZeroVector;
	brick_position.X = GetActorLocation().X + (distace_spawn_x * count_x);
	brick_position.Y = 0;
	brick_position.Z = GetActorLocation().Z + (distace_spawn_z * count_z);
	return brick_position;
}


// Called every frame
void AGeneracion_ladrillos::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

