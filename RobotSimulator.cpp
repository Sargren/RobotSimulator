// RobotSimulator.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include "robot.h"
#include <assert.h> 

using namespace std;

int main()
{
	//Examples
	int testDirection(0);

	Robot robot;	
	robot.TestFile("exampleA.txt",testDirection);
	robot.TestFile("exampleB.txt", testDirection);
	robot.TestFile("exampleC.txt", testDirection);

	//Tests:
	coords testCoords;
	robot.TestFile("Test1.txt", testDirection, testCoords);
	assert(testCoords.x == 3);
	assert(testCoords.y == 3);
	assert(testDirection == direction::SOUTH);

	robot.TestFile("Test2.txt", testDirection, testCoords);
	assert(testCoords.x == 0);
	assert(testCoords.y == 0);
	assert(testDirection == direction::SOUTH);

	robot.TestFile("Test3.txt", testDirection, testCoords);
	assert(testCoords.x == 4);
	assert(testCoords.y == 4);
	assert(testDirection == direction::EAST);

	robot.TestFile("Test4.txt", testDirection, testCoords);
	assert(testCoords.x == 2);
	assert(testCoords.y == 2);
	assert(testDirection == direction::NORTH);


	cin.get();	//Wait for user interaction.

    return 0;
}

