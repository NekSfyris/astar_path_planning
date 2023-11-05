#include <A_star.h>


// Default constructor
AStar::AStar(Grid* grid): grid(grid)
{
}

void AStar::initPlanner(const Cell& start, const Cell& goal)
{
 
    // Clear any previous path and open/closed lists
    path_to_goal.clear();
    openList.clear();
    closedList.clear();

    // Cell objects to Node objects
    Node startNode = {start.row, start.col, 0, 0, 0, nullptr};
    Node goalNode = {goal.row, goal.col, 0, 0, 0, nullptr};

    // add the initial node to the open list
    int g = 0;
    int h = calcHeuristicEuclidean(startNode, goalNode);
    int f = g + h;
    Node initNode = {startNode.row, startNode.col, g, h, f, nullptr};
    openList.push_back(initNode);

    cout << "Planning Initilized!" << endl;

}

bool AStar::step(const Cell& goal)
{

    pathFound = false;

    // Cell objects to Node objects
    Node goalNode = {goal.row, goal.col, 0, 0, 0, nullptr};

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

    // get new current node
    Node currNode = openList[minIndex];

    // remove previous node from the open list
    openList.erase(openList.begin() + minIndex);

    // add current node to the closed list
    closedList.push_back(currNode);

    // if current node is the goal node, then we found the path
    if(currNode.row == goal.row && currNode.col == goal.col) 
    {
        // Goal reached, reconstruct the path
        Node* node = &currNode;
        while(node != nullptr) 
        {
            path_to_goal.insert(path_to_goal.begin(), Cell(node->row, node->col, grid->getNumRows(), grid->getNumColumns()));
            node = node->parent;
        }

        pathFound = true;
        return pathFound;
    }


    // get neighbors of the current node
    std::vector<Node> neighbors = grid->getNeighborCells(currNode);

    // find the next "lowest" cost neighbor
    for(Node& neighbor : neighbors) 
    {

        // chck if neighbor is in the closed list
        bool foundInClosedList = false;
        for(const Node& closedNode : closedList) 
        {
            if (neighbor == closedNode) 
            {
                foundInClosedList = true;
                break;
            }
        }
        //continue if neighbor is in the closed list
        if(foundInClosedList)
        {
            continue;
        }
            

        // compute tentative g cost
        int g_cost = currNode.g + calcCostEuclidean(currNode, neighbor);

        // check if neighbor is in the open list
        bool inOpenList = false;
        for(Node& openNode : openList) 
        {
            if(openNode.row == neighbor.row && openNode.col == neighbor.col)
            {
                inOpenList = true;
                if(g_cost < openNode.g)
                {
                    openNode.g = g_cost;
                    openNode.h = calcHeuristicEuclidean(openNode, goalNode);
                    openNode.f = openNode.g + openNode.h;
                    openNode.parent = &currNode;
                }
                break;
            }
        }

        // if neighbor is not in open list, add it
        if(!inOpenList)
        {
            neighbor.g = g_cost;
            neighbor.h = calcHeuristicEuclidean(neighbor, goalNode);
            neighbor.f = neighbor.g + neighbor.h;
            neighbor.parent = &currNode;
            openList.push_back(neighbor);
        }
    }

    return pathFound;

}

int AStar::calcCostEuclidean(const Node& current, const Node& neighbor)
{
    // Euclidean distance between current and neighbor node
    int dx = neighbor.row - current.row;
    int dy = neighbor.col - current.col;
    
    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

int AStar::calcCostManhattan(const Node& current, const Node& neighbor)
{
    // Manhattan distance (sum of absolute differences in x and y)
    int dx = std::abs(neighbor.row - current.row);
    int dy = std::abs(neighbor.col - current.col);

    int cost = dx + dy;
    cost *= 10; // just for simplicity in numbers

    return cost;
}

int AStar::calcHeuristicEuclidean(const Node& current, const Node& goal)
{
    // Euclidean distance between current and neighbor node
    int dx = goal.row - current.row;
    int dy = goal.col - current.col;
    
    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

int AStar::calcHeuristicManhattan(const Node& current, const Node& goal)
{
    // Manhattan distance (sum of absolute differences in x and y)
    int dx = std::abs(goal.row - current.row);
    int dy = std::abs(goal.col - current.col);

    int cost = dx + dy;
    cost *= 10; // just for simplicity in numbers

    return cost;
}




// std::vector<Cell> AStar::getPath() const
// {
//     cout << "NOT IMPLEMENTED YET!" << endl;
// }

