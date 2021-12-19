// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MazeGenerator.generated.h"

/**
 *
*/
UCLASS()
class MAZE_API AMazeGenerator : public AActor
{
	GENERATED_BODY()
	
public:	
	/**
	 * Sets default values for this actor's properties
	*/
	AMazeGenerator();

	UPROPERTY(EditAnywhere, Category = "Environment")
	TSubclassOf<class AWall> BP_Wall;
	UPROPERTY(EditAnywhere, Category = "Environment")
	TSubclassOf<class AFloor> BP_Floor;
	UPROPERTY(EditAnywhere, Category = "Environment")
	int height = 5;
	UPROPERTY(EditAnywhere, Category = "Environment")
	int width = 6;

protected:
	/**
	 * Called when the game starts or when spawned
	*/

	virtual void BeginPlay() override;

public:	
	/**
	 * Called every frame
	 * @param DeltaTime Game time elapsed during last frame modified by the time dilation 
	*/
	virtual void Tick(float DeltaTime) override;

};
