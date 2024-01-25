#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <memory>
#include <cmath>

using namespace std;


// struct for each node of 2D grid
struct Node 
{
    int row;            // node's row position
    int col;            // node's col position
    int g;              // cost from the start node to this node
    int h;              // heuristic (estimated cost to goal)
    int f;              // total cost = g + h
    std::shared_ptr<Node> parent;       // parent node

    // // Overload the equality operator
    // bool operator==(const Node& compare_node) const 
    // {
    //     return (row == compare_node.row) && (col == compare_node.col);
    // }

    // default constructor
    Node(int r, int c, int costG, int costH, std::shared_ptr<Node> parentNode = nullptr)
        : row(r), col(c), g(costG), h(costH), f(costG + costH), parent(parentNode) 
    {}

};

// states of SDL process
enum SDLState 
{
    OBSTACLE_SELECTION,
    PATH_PLANNING
};

// states of path planner output
enum PlannerState 
{
    INIT,
    EXPLORING,
    NO_PATH,
    PATH_FOUND,
    FINISH
};

// check i cell is inside the boundaries of the defined grid
inline bool isValidCell(int x, int y, int numRows, int numColumns) 
{
    return (x >= 0 && x < numRows && y >= 0 && y < numColumns);
}


// For G score. 
// This cost is typically determined by factors like terrain, movement cost, or other considerations specific to the application or map
inline int calcCostEuclidean(std::shared_ptr<Node> current, const Node& neighbor)
{
    // Euclidean distance between current and neighbor node
    int dx = neighbor.row - current->row;
    int dy = neighbor.col - current->col;
    
    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

inline int calcCostEuclidean(const Node& current, std::shared_ptr<Node> neighbor)
{
    // Euclidean distance between current and neighbor node
    int dx = neighbor->row - current.row;
    int dy = neighbor->col - current.col;
    
    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

inline int calcCostEuclidean(const Node& current, const Node& neighbor)
{
    // Euclidean distance between current and neighbor node
    int dx = neighbor.row - current.row;
    int dy = neighbor.col - current.col;
    
    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

inline int calcCostManhattan(const Node& current, const Node& neighbor)
{
    // Manhattan distance (sum of absolute differences in x and y)
    int dx = std::abs(neighbor.row - current.row);
    int dy = std::abs(neighbor.col - current.col);

    int cost = dx + dy;
    cost *= 10; // just for simplicity in numbers

    return cost;
}

//----------------------------------------
inline int calcCostElevationEuclidean(const Node& current, const Node& neighbor)
{
    // Euclidean distance between current and neighbor node
    int dx = neighbor.row - current.row;
    int dy = neighbor.col - current.col;
    int de = neighbor.elevation - current.elevation;
    
    int cost = std::sqrt(dx * dx + dy * dy + de * de);
    cost *= 10; // just for simplicity in numbers

    return cost;
}
//----------------------------------------

// For H score. 
// The Heuristic cost typically involves distance metrics like the Manhattan distance or Euclidean distance from the current node to the goal one
inline int calcHeuristicEuclidean(std::shared_ptr<Node> current, std::shared_ptr<Node> goal)
{
    // Euclidean distance between current and neighbor node
    int dx = goal->row - current->row;
    int dy = goal->col - current->col;
    
    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

inline int calcHeuristicEuclidean(const Node& current, std::shared_ptr<Node> goal)
{
    // Euclidean distance between current and neighbor node
    int dx = goal->row - current.row;
    int dy = goal->col - current.col;
    
    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

inline int calcHeuristicEuclidean(std::shared_ptr<Node> current, const Node& goal)
{
    // Manhattan distance (sum of absolute differences in x and y)
    int dx = goal.row - current->row;
    int dy = goal.col - current->col;

    int cost = std::sqrt(dx * dx + dy * dy);
    cost *= 10; // just for simplicity in numbers

    return cost;
}

inline int calcHeuristicManhattan(const Node& current, const Node& goal)
{
    // Manhattan distance (sum of absolute differences in x and y)
    int dx = std::abs(goal.row - current.row);
    int dy = std::abs(goal.col - current.col);

    int cost = dx + dy;
    cost *= 10; // just for simplicity in numbers

    return cost;
}


// print all node attributes
inline void printNode(std::shared_ptr<Node> node)
{
    if(node->parent != nullptr)
    {
        cout << "node row="<< node->row<<", col=" << node->col << ", parent_row=" << node->parent->row << ", parent_col="<< node->parent->col << ", g="<< node->g << ", h="<< node->h << ", f="<< node->f << endl;
    }
    else
    {
        cout << "node row="<< node->row<<", col=" << node->col << ", g="<< node->g << ", h="<< node->h << ", f="<< node->f << endl;
    }
}

// print vector of Nodes
inline void printVector(std::vector<std::shared_ptr<Node>> nodeVector)
{
    std::cout << "************************* PRINTING Vector ********************************" << std::endl;
    for(int i=0; i<nodeVector.size(); i++)
    {
        std::shared_ptr<Node> node = nodeVector[i];

        printNode(node);
    }
    std::cout << "****************************************************************" << std::endl;
}



#endif