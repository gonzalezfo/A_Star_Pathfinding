#include "..\include\Maze.h"
#include <list>
#include <string>
#include <iostream>

Maze::Maze()
{
    width_ = -1;
    height_ = -1;
    cells_ = nullptr;
    start_cell_ = nullptr;
    end_cell_ = nullptr;
}

Maze::~Maze() {}

Cell& Maze::cell(int row, int col)
{
    return cells_[(width_ * row) + col];
}

void Maze::init(int width, int height)
{
    if (width > 0) 
    {
        width_ = width;
    }

    if (height > 0) 
    {
        height_ = height;
    }

    cells_ = new Cell[width_ * height_];

    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            cells_[y * width + x].col = x;
            cells_[y * width + x].row = y;
            cells_[y * width + x].type = kTileType_Void;
            cells_[y * width + x].globalGoal = INFINITY;
            cells_[y * width + x].localGoal = INFINITY;
            cells_[y * width + x].parent = nullptr;
            cells_[y * width + x].bvisited = false;
        }
    }
}

void Maze::connectCells()
{
    for (int x = 0; x < width_; x++)
    {
        for (int y = 0; y < height_; y++)
        {
			// Make sure that the cells are inside the bounds
            if (y > 0) 
                cells_[y * width_ + x].neighbours.push_back(&cells_[(y - 1) * width_ + (x + 0)]);
            if (y < height_ - 1)
                cells_[y * width_ + x].neighbours.push_back(&cells_[(y + 1) * width_ + (x + 0)]);
            if (x > 0)
                cells_[y * width_ + x].neighbours.push_back(&cells_[(y + 0) * width_ + (x - 1)]);
            if (x < width_ - 1)
                cells_[y * width_ + x].neighbours.push_back(&cells_[(y + 0) * width_ + (x + 1)]);
        }
    }
}

bool Maze::isNorth(Cell* c1, Cell* c2)
{
    if (c1->col == c2->col && c1->row < c2->row)
    {
        return true;
    }
    return false;
}

bool Maze::isEast(Cell* c1, Cell* c2)
{
    if (c1->col > c2->col && c1->row == c2->row)
    {
        return true;
    }
    return false;
}

bool Maze::isSouth(Cell* c1, Cell* c2)
{
    if (c1->col == c2->col && c1->row > c2->row)
    {
        return true;
    }
    return false;
}

bool Maze::isWest(Cell* c1, Cell* c2)
{
    if (c1->col < c2->col && c1->row == c2->row)
    {
        return true;
    }
    return false;
}



bool Maze::findPath()
{
	connectCells();  // Connect the cells with their neighbours


    auto distance = [](Cell* a, Cell* b) 
    {
        return sqrtf((float)((a->col - b->col) * (a->col - b->col) + (a->row - b->row) * (a->row - b->row)));
    };

    // Puts the start cell with initial values and sets as current
    start_cell_->localGoal = 0.0f;
    start_cell_->globalGoal = distance(start_cell_, end_cell_);
    Cell* cellCurrent = start_cell_;

	// Creation of the list to push all the non-visited cells
    std::list<Cell*> notTestedCells;
    notTestedCells.push_back(start_cell_);


    while (!notTestedCells.empty())
    {
		// Sort the non-visited cells by global param
        notTestedCells.sort([](const Cell* c1, const Cell* c2) { return c1->globalGoal < c2->globalGoal; });

        while (!notTestedCells.empty() && notTestedCells.front()->bvisited)
            notTestedCells.pop_front();

		// breaks the while if there are not cells left
        if (notTestedCells.empty())
            break;

        cellCurrent = notTestedCells.front();
        cellCurrent->bvisited = true; // sets the cell as visited, not to consider it again

		// Checks all the neighbour nodes of the current node
        for (auto cellNeighbour : cellCurrent->neighbours)
        {
			if (!cellNeighbour->bvisited && cellNeighbour->type != kTileType_Wall)
			{
                notTestedCells.push_back(cellNeighbour); // puts in the vector if it's not a wall and has not been visited

				// The potential lowest distance
				float fPossiblyLowerGoal = cellCurrent->localGoal + distance(cellCurrent, cellNeighbour);

				// Sets the path if the potential distance is smaller than the neighbours'
				if (fPossiblyLowerGoal < cellNeighbour->localGoal)
				{
					cellNeighbour->parent = cellCurrent;
					cellNeighbour->localGoal = fPossiblyLowerGoal;

					// updates the neighbour score as the path length has been changed
					cellNeighbour->globalGoal = cellNeighbour->localGoal + distance(cellNeighbour, end_cell_);
				}
			}
        }
    }

	if (end_cell_->parent != nullptr)
	{
		return true;
	}
	else 
	{
		std::cout << "[ERROR]: Maze has no solution" << std::endl;
		return false;
	}
}


void Maze::debugPrint()
{
    for (int row = 0; row < height_; ++row) {
        for (int col = 0; col < width_; ++col) {
            if (cell(row, col).type == kTileType_Normal) {
                printf(".");
            }
            else if (cell(row, col).type == kTileType_Wall) {
                printf("x");
            }
            else if (cell(row, col).type == kTileType_Start) {
                printf("A");
            }
            else if (cell(row, col).type == kTileType_End) {
                printf("B");
            }
            else {
                printf("Z");
            }
        }
        printf("\n");
    }
}


void Maze::instructionStringPrint()
{
    std::string instructions;

    if (end_cell_ != nullptr)
    {
        Cell* cell = end_cell_;
        while (cell->parent != nullptr)
        {

            if (isNorth(cell, cell->parent))
                instructions.append(" N");
            else if (isEast(cell, cell->parent))
                instructions.append(" E");
            else if (isWest(cell, cell->parent))
                instructions.append(" W");
            else if (isSouth(cell, cell->parent))
                instructions.append(" S");


            // Set next node to this node's parent
            cell = cell->parent;
        }
	}

	// Reverses the string as the path is set from end to beggining
    for (int i = 0; i < instructions.length() / 2; i++)
    {
        std::swap(instructions[i], instructions[instructions.length() - i - 1]);
    }
	std::cout << "\n" << "Solution: ";
    std::cout << instructions << std::endl;
}

void Maze::setStartCell(Cell* cell)
{
    start_cell_ = cell;
}

void Maze::setEndCell(Cell* cell)
{
    end_cell_ = cell;
}
