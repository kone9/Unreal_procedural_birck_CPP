// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Generacion_ladrillos.generated.h"

UCLASS()
class PROCEDURAL_BRICKS_API AGeneracion_ladrillos : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGeneracion_ladrillos();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	//timer
	FTimerHandle timer_spawn_handler;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float timeToSpawn;
	
	UFUNCTION()
	void SpawnTimer_out();

	//determines the type of instance according to the selected condition
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool horizontal_can_instantiate_bricks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool vertical_can_instantiate_bricks;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool diagonal_can_instantiate_bricks;

	//birck
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int amount_z;


	//new position brick
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int distace_spawn_x;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int distace_spawn_z;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> brick_reference;
	
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int check_X_counter;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int check_Z_counter;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int check_offset_X;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	int check_offset_Z;

private:
	void spawn_brick(TSubclassOf<AActor> brick, FVector positionBrick);
	
	//instance checks positions
	bool horizontal_new_position_to_end(FVector& brick_position);
	bool vertical_new_position_to_end(FVector& brick_position);
	bool diagonal_new_position_to_end(FVector& brick_position);

	//counter reference actual position
	int count_x;
	int count_z;


	int offset_x;
	int offset_z;
	bool can_spawn;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;




};
