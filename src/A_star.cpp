#include <A_star.h>
#include "utils.h"

// Default constructor
AStar::AStar(Grid* grid): grid(grid)
{
}

bool AStar::initPlanner(const Cell& start, const Cell& goal)
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

bool AStar::step(const Cell& goal)
{
    // if no path found
    if(openList.empty()) 
    {
        return true;
    }

    // last node is the "lowest" previous score node
    int minCost = openList[0].f;
    int minIndex = 0;

    // find the next node with the lowest total cost
    for(int i = 1; i < openList.size(); i++) 
    {
        if(openList[i].f < minCost) 
        {
            minCost = openList[i].f;
            minIndex = i;
        }
    }

    // get new node
    Node currNode = openList[minIndex];

    // remove previous node from the open list
    openList.erase(openList.begin() + minIndex);

    // add new node to the closed list
    closedList.push_back(currentNode);

    // if we reached the goal
    if(currentNode.x == goal.x && currentNode.y == goal.y) 
    {
        // Goal reached, reconstruct the path
        Node* node = &currentNode;
        while(node != nullptr) 
        {
            path_to_goal.insert(path_to_goal.begin(), Cell(node->x, node->y));
            node = node->parent;
        }
        pathFound = true;
        return pathFound;
    }


    // get neighbors of the current node
    std::vector<Node> neighbor_cells = grid->getNeighborCells(currentNode);


/////////////


    for(const Node& neighbor : neighbor_cells) 
    {
        // continue if neighbor is in the closed list
        if(std::find(closedList.begin(), closedList.end(), neighbor) != closedList.end())
        {
            continue;
        }

        // Calculate tentative g score
        int tentativeG = currentNode.g + grid->calculateCost(currentNode, neighbor);

        // Check if the neighbor is in the open list
        bool inOpenList = false;
        for(Node& openNode : openList) 
        {
            if(openNode.x == neighbor.x && openNode.y == neighbor.y)
            {
                inOpenList = true;
                if(tentativeG < openNode.g)
                {
                    openNode.g = tentativeG;
                    openNode.parent = &currentNode;
                }
                break;
            }
        }

        // If neighbor is not in open list, add it
        if(!inOpenList)
        {
            neighbor.g = tentativeG;
            neighbor.h = grid->calculateHeuristic(neighbor, goal);
            neighbor.parent = &currentNode;
            openList.push_back(neighbor);
        }
    }

    pathFound = false;
    return pathFound;

}

int AStar::calcCostEuclidean(const Node& current, const Node& neighbor)
{
    // Euclidean distance between current and neighbor node
    int dx = neighbor.x - current.x;
    int dy = neighbor.y - current.y;
    
    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

int AStar::calcCostManhattan(const Node& current, const Node& neighbor)
{
    // Manhattan distance (sum of absolute differences in x and y)
    int dx = std::abs(neighbor.x - current.x);
    int dy = std::abs(neighbor.y - current.y);

    int cost = dx + dy;
    cost *= 10; // just for simplicity in numbers

    return cost;
}



std::vector<Cell> AStar::getPath() const
{

}

