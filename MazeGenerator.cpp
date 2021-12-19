// Fill out your copyright notice in the Description page of Project Settings.


#include "MazeGenerator.h"
#include "Wall.h"
#include "Floor.h"
#include "Math/TransformNonVectorized.h"
#include "Math/Quat.h"

/**
 * Sets default values
*/
AMazeGenerator::AMazeGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}
int* shuffle(int* a)
{

	for (int i = 0; i < 4; i++)
	{
		a[i] = i;
	}
	int ArrayLength = 4;
	while (ArrayLength > 0)
	{
		int RandomPlace = rand() % ArrayLength;
		int temp;
		temp = a[ArrayLength - 1];
		a[ArrayLength - 1] = a[RandomPlace];
		a[RandomPlace] = temp;
		ArrayLength -= 1;
	}

	return a;
}

char* GenerateMaze(char* m, int MHeight, int MWidth, int Height, int Width, int x, int y)
{
	int Directions[4];
	int DirectionValue = 2;
	int* ShuffledDirections;
	ShuffledDirections = shuffle(Directions);
	ShuffledDirections = shuffle(ShuffledDirections);
	for (int i = 0; i < 4; i++)
	{
		int nx, ny, wx, wy;
		if (ShuffledDirections[i] == 0)
		{
			nx = x - 2;
			ny = y;
			wx = x - 1;
			wy = y;
		}
		if (ShuffledDirections[i] == 1)
		{
			nx = x + 2;
			ny = y;
			wx = x + 1;
			wy = y;
		}
		if (ShuffledDirections[i] == 2)
		{
			nx = x;
			ny = y - 2;
			wx = x;
			wy = y - 1;
		}
		if (ShuffledDirections[i] == 3)
		{
			nx = x;
			ny = y + 2;
			wx = x;
			wy = y + 1;
		}
		if ((nx > 0 && nx < MHeight && ny>0 && ny < MWidth) && *(m + nx * MWidth + ny) == '2')
		{
			*(m + x * MWidth + y) = ' ';
			*(m + wx * MWidth + wy) = ' ';
			*(m + nx * MWidth + ny) = ' ';
			m = GenerateMaze(m, MHeight, MWidth, Height, Width, nx, ny);
		}

	}
	return m;
}

/**
 * Called when the game starts or when spawned
*/
void AMazeGenerator::BeginPlay()
{
	Super::BeginPlay();
	if (HasAuthority())
	{
		int MazeHeight = 2 * height + 1;
		int MazeWidth = 2 * width + 1;

		char* maze = new char[MazeWidth * MazeHeight];
		for (int i = 0; i < MazeHeight; i++)				//initializes Maze with default values of walls and unvisited cells.
		{
			for (int j = 0; j < MazeWidth; j++)
				if (i % 2 != 0 && j % 2 != 0)
					*(maze + i * MazeWidth + j) = '2';		//unvisited cells are initialised as 2
				else
					*(maze + i * MazeWidth + j) = '#';		//walls are initialized as #
		}
		for (int i = 0; i < MazeHeight; i += 1)
		{
			for (int j = 0; j < MazeWidth; j += 1)
			{
				//cout<<i<<" "<<j<<" "<<*(maze+i*width+j)<<endl;
				if (*(maze + i * MazeWidth + j) == '2')
				{
					maze = GenerateMaze(maze, MazeHeight, MazeWidth, height, width, i, j);
				}

			}
		}
		FTransform spawnTransform = GetActorTransform();

		for (int i = 0; i < MazeHeight; i++)
		{
			for (int j = 0; j < MazeWidth; j++)
			{
				spawnTransform.SetLocation(FVector(i * 400, j * 400, 0));
				GetWorld()->SpawnActor<AFloor>(BP_Floor, spawnTransform);
			}

		}

		for (int i = 0; i < MazeHeight; i++)
		{
			for (int j = 0; j < MazeWidth; j++)
			{
				if (*(maze + i * MazeWidth + j) == '#')
				{
					spawnTransform = GetActorTransform();
					if (i % 2 == 0 && j % 2 != 0)
					{

						spawnTransform.SetLocation(FVector(i * 400, j * 400 - 400, 0));
						spawnTransform.SetRotation(FQuat::MakeFromEuler(FVector(0, 0, 90)));
						GetWorld()->SpawnActor<AWall>(BP_Wall, spawnTransform);
					}
					if (i % 2 != 0 && j % 2 == 0)
					{

						spawnTransform.SetLocation(FVector(i * 400 - 400, j * 400, 0));

						spawnTransform.SetRotation(FQuat::MakeFromEuler(FVector(0, 0, 0)));
						GetWorld()->SpawnActor<AWall>(BP_Wall, spawnTransform);
					}
				}

			}

		}
	}
	
	

}

/**
 * Called every frame
 * @param DeltaTime Game time elapsed during last frame modified by the time dilation
*/
void AMazeGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

