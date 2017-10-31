#pragma once
#include <string>
#include <fstream>	//ifstream..
#include <iostream>	//cout..

typedef struct { short x, y; } coords;
enum class CMD { PLACE, MOVE, LEFT, RIGHT, REPORT, ILLEGAL };
enum  direction { NORTH = 0, EAST, SOUTH, WEST };


class Robot
{
private:
	coords currentCoords;
	direction currentDirection;

public:
	CMD ParseLine(std::string line, coords& _coords, direction& _dir);
	bool performCMD(CMD currentCMD, coords theCoords, direction theDir);
	bool TestFile(std::string fileName, int& finalDirection, coords& finalCoords = coords());
};
