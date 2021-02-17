#ifndef __MAZE_H__
#define __MAZE_H__ 1

#include <stack>
#include <array>
#include <set>
#include <vector>


enum TileType
{
	kTileType_Void = 0,// Non-Walkable
	kTileType_Wall, 
	kTileType_Normal, // First of walkables
	kTileType_Start,
	kTileType_End
};

struct Cell {
	int type;							// Type of Tiletype of the cell
	bool bvisited = false;				// Is this cell have been searched already?
	float globalGoal;					// Distance to Goal so far
	float localGoal;					// Distance to Goal if we took an alternative path
	int col;				
	int row;
	std::vector<Cell*> neighbours;		// Vector to store each of its neighbours
	Cell* parent;						// Cell connecting to this cell leads the shortest path
};

class Maze
{
public:
	Maze();
	~Maze();

	/* Return the cells requested by row and col index */
	Cell& cell(int row, int col);

	/* Initializes the variables with the the given values from the file */
	void init(int width, int height);

	/* Each cell connects with their neighbours via the vector */
	void connectCells();

	/* Check where a cell is compared to other cell */
	bool isNorth(Cell* c1, Cell* c2);
	bool isEast(Cell* c1, Cell* c2);
	bool isSouth(Cell* c1, Cell* c2);
	bool isWest(Cell* c1, Cell* c2);

	/* Executes the pathfinder algorithm */
	bool findPath();

	/* DEBUG print */
	void debugPrint();
	void instructionStringPrint();

	/* Private vars setters */
	void setStartCell(Cell* cell);
	void setEndCell(Cell* cell);

private:

	int width_;
	int height_;

	// Cell pointers
	Cell* cells_;
	Cell* start_cell_;
	Cell* end_cell_;

};

#endif