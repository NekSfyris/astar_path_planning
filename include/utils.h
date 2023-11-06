#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <map>

using namespace std;


// struct for each node of 2D grid
struct Node 
{
    int row;            // node's row position
    int col;            // node's col position
    int g;              // cost from the start node to this node
    int h;              // heuristic (estimated cost to goal)
    int f;              // total cost = g + h
    Node* parent;       // parent node

    // Overload the equality operator
    bool operator==(const Node& compare_node) const 
    {
        return (row == compare_node.row) && (col == compare_node.col);
    }
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
    EXPLORING,
    NO_PATH,
    PATH_FOUND
};


//map of planner output states with messages
map <PlannerState, string> planner_output = { 
    {EXPLORING, "STILL EXPLORING MAP!"}, 
    {NO_PATH, "NO PATH AVAILABLE TO GOAL!"}, 
    {PATH_FOUND, "PATH WAS FOUND!"}
};


inline bool isValidCell(int x, int y, int numRows, int numColumns) 
{
    return (x >= 0 && x < numRows && y >= 0 && y < numColumns);
}

#endif