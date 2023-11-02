#include <A_star.h>
#include "utils.h"

// Default constructor
AStar::AStar(Grid* grid): grid(grid)
{
}

bool AStar::initPlanning(const Cell& start, const Cell& goal)
{
 
    // Clear any previous path and open/closed lists
    path.clear();
    openList.clear();
    closedList.clear();


    // Add the initial node to the open list
    int g = 0;
    int h = grid->calcHeuristic(start, goal);
    int f = g + h;
    Node initNode = {start.x, start.y, g, h, f, nullptr};
    openList.push_back(initNode);

    cout << "Planning Initilized!" << endl;

}

bool AStar::step()
{

}

std::vector<Cell> AStar::getPath() const
{

}

