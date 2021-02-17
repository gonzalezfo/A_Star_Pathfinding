#include "Loader.h"

#include <cstdio>
#include <iostream>
#include <array>
#include <fstream>
#include <streambuf>


bool MazeIntegrityChecker(std::string str)
{
	bool isStart = false;
	bool isEnd = false;

	for (int i = 0; i < str.size() - 1; ++i)
	{
		if (str[i] == 'A')
		{
			isStart = true;
		}

		if (str[i] == 'B')
		{
			isEnd = true;
		}
	}

	if (isStart && isEnd)
	{
		return true;
	}

	return false;
}


bool GenerateMazeFromFile(Maze* maze, std::string filename)
{
	// Check parameter errors
	if (filename.empty())
	{
		std::cout << ("[ERROR]: Filename is NULL") << std::endl;
		return false;
	}

	if (maze == nullptr)
	{
		std::cout << ("[ERROR]: Maze is NULL") << std::endl;
		return false;
	}


	// Loads the file and puts in a string
	std::ifstream file(filename);
	std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

	// Checks if the string has been filled
	if (contents.empty())
	{
		std::cout << ("[ERROR]: File is Empty or does not exist");
		return false;
	}

	if (!MazeIntegrityChecker(contents))
	{
		std::cout << ("[ERROR]: Map does not have Start or End Point") << std::endl;
		return false;
	}

	int total_rows = 1; // starting at 1 because if file not empty there's already one row

	for (int i = 0; i < contents.size() - 1; ++i)
	{
		if (contents[i] == '\n')
		{
			total_rows++;
			contents.erase(i, 1); //erase \n characters from the string
		}
	}

	int total_cols = int(contents.size()) / total_rows;

	maze->init(total_cols, total_rows);

	// Sets the cells to the type of cell depending on the character
	for (int row = 0; row < total_rows; ++row)
	{
		for (int col = 0; col < total_cols; ++col)
		{
			int tmp_idx = (total_cols * row) + col;

			switch (contents[tmp_idx])
			{
			case 'x':
				maze->cell(row, col).type = kTileType_Wall;
				break;
			case '.':
				maze->cell(row, col).type = kTileType_Normal;
				break;
			case 'A':
				maze->cell(row, col).type = kTileType_Start;
				maze->setStartCell(&maze->cell(row, col));
				break;
			case 'B':
				maze->cell(row, col).type = kTileType_End;
				maze->setEndCell(&maze->cell(row, col));
				break;
			default:
				maze->cell(row, col).type = kTileType_Void;
				break;
			}
		}
	}
	return true;
}
