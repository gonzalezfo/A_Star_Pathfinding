#ifndef __LOADER_H__
#define __LOADER_H__ 1

#include "Maze.h"
#include <string>

/* Checks if the Maze has Starting and End Point */
bool MazeIntegrityChecker(std::string str);

/* Loads the file of the map and generates a Maze from the data in it */
extern bool GenerateMazeFromFile(Maze* maze, std::string filename);


#endif