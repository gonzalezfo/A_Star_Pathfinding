#include "Loader.h"
#include "Maze.h"
#include <iostream>
#include <string>

int main()
{
	Maze maze;

	std::cout << "Welcome to Jesus Gonzalez's A* Pathfinder" << std::endl;
	std::cout << "Select the number of the file you want to solve" << std::endl;


	std::string filename = "../data/quickest_route_";
	std::string aux;
	std::cin >> aux;
	filename = filename + aux + ".txt";


	if (GenerateMazeFromFile(&maze, filename))
	{
		maze.debugPrint();
		if (maze.findPath())
		{
			maze.instructionStringPrint();
		}
	}

	system("PAUSE");

	return 0;
}