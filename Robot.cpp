//#include "stdafx.h"
#include "Robot.h"
#include <sstream>	//istringstream



direction operator++(direction d)
{
	switch (d)
	{
	case direction::NORTH: return direction::EAST;
	case direction::EAST: return direction::SOUTH;
	case direction::SOUTH: return direction::WEST;
	case direction::WEST: return direction::NORTH;
	}
}

direction operator--(direction d)
{
	switch (d)
	{
	case direction::NORTH: return direction::WEST;
	case direction::WEST: return direction::SOUTH;
	case direction::SOUTH: return direction::EAST;
	case direction::EAST: return direction::NORTH;
	}
}

std::ostream& operator<<(std::ostream& os, const direction& d)
{
	switch (d)
	{
	case direction::NORTH: os << "NORTH"; break;
	case direction::WEST: os << "WEST"; break;
	case direction::SOUTH: os << "SOUTH"; break;
	case direction::EAST: os << "EAST"; break;
	}
	return os;
}


bool Robot::performCMD(CMD currentCMD, coords theCoords, direction theDir)
{
	switch (currentCMD)
	{
	case CMD::PLACE:
	{
		if (0 <= theCoords.x && theCoords.x < 5 && 0 <= theCoords.y && theCoords.y < 5)
		{
			currentCoords = theCoords;
			currentDirection = theDir;
			return true;
		}
		return false;
	}
	case CMD::LEFT:
	{
		currentDirection = --currentDirection;
		return true;
	}
	case CMD::RIGHT:
	{
		currentDirection = ++currentDirection;
		return true;
	}
	case CMD::MOVE:
	{
		switch (currentDirection)
		{
		case direction::NORTH:
		{
			if (currentCoords.y < 4)
			{
				currentCoords.y++;
				return true;
			}
			return false;
		}
		case direction::EAST:
		{
			if (currentCoords.x < 4)
			{
				currentCoords.x++;
				return true;
			}
			return false;
		}
		case direction::SOUTH:
		{
			if (currentCoords.y > 0)
			{
				currentCoords.y--;
				return true;
			}
			return false;
		}
		case direction::WEST:
		{
			if (currentCoords.x > 0)
			{
				currentCoords.x--;
				return true;
			}
			return false;
		}
		}

		return false;
	}
	case CMD::REPORT:
	{
		std::cout << "Position (" << currentCoords.x << "," << currentCoords.y << ") Facing " << currentDirection << "." << std::endl;
		return true;
	}
	}
	return false;
}

CMD Robot::ParseLine(std::string line, coords& _coords, direction& _dir)
{
	const std::string first4 = line.substr(0, 4);
	if (first4 == "MOVE")	return CMD::MOVE;
	if (first4 == "LEFT")	return CMD::LEFT;

	const std::string first5 = line.substr(0, 5);
	if (first5 == "RIGHT")	return CMD::RIGHT;
	if (first5 == "PLACE")
	{
		std::size_t pos = line.find(",",5);
		if (pos == std::string::npos)
			return CMD::ILLEGAL;

		short x;
		try
		{
			std::string line2 = line.substr(6, pos - 5);
			x = std::stoi(line2);
		}
		catch (...)
		{
			return CMD::ILLEGAL;
		}

		std::size_t pos2 = line.find(",", pos+1);
		if (pos2 == std::string::npos)
			return CMD::ILLEGAL;

		short y;
		try
		{
			std::string line3 = line.substr(pos+1, pos2 - pos-1);
			y = std::stoi(line3);
		}
		catch (...)
		{
			return CMD::ILLEGAL;
		}

		_coords = coords{ x, y };


		const std::string line4 = line.substr(pos2 + 1);		
		if (line4 == "EAST")
			_dir = direction::EAST;
		else if (line4 == "WEST")
			_dir = direction::WEST;
		else if (line4 == "NORTH")
			_dir = direction::NORTH;
		else if (line4 == "SOUTH")
			_dir = direction::SOUTH;
		else return CMD::ILLEGAL;

		return CMD::PLACE;
	}
		
	if (line.substr(0, 6) == "REPORT")	return CMD::REPORT;

	return CMD::ILLEGAL;
}

bool Robot::TestFile(std::string fileName, int& finalDirection, coords& finalCoords)
{
	std::string line;
	std::ifstream myfile(fileName);
	if (myfile.is_open())
	{
		bool foundPlace{ false };

		std::cout << std::endl << "Running " << fileName << std::endl;
		while (getline(myfile, line))
		{
			std::cout << line << '\n';
			coords theCoords;
			direction theDir;
			CMD currentCMD = ParseLine(line, theCoords, theDir);

			if (!foundPlace && currentCMD != CMD::PLACE)
				continue;

			bool success = false;
			if (currentCMD != CMD::ILLEGAL)
				success = performCMD(currentCMD, theCoords, theDir);


			if (currentCMD == CMD::PLACE && success)
				foundPlace = true;
		}
		myfile.close();

		finalCoords		= currentCoords;
		finalDirection	= currentDirection;
		return true;
	}
	else std::cout << "Unable to open file";
	return false;
}
