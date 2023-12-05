#ifndef UTILS_H
#define UTILS_H

#include <vector>

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

    // // Constructor for deep copying
    // Node(const Node& other) 
    // {
    //     row = other.row;
    //     col = other.col;
    //     g = other.g;
    //     h = other.h;
    //     f = other.f;

    //     // Perform a deep copy of the parent node
    //     if (other.parent != nullptr) 
    //     {
    //         parent = new Node(*other.parent); // Deep copy of the parent node
    //     } 
    //     else 
    //     {
    //         parent = nullptr;
    //     }
    // }

    // Overload the equality operator
    bool operator==(const Node& compare_node) const 
    {
        return (row == compare_node.row) && (col == compare_node.col);
    }

    // // Overload the assignment operator
    // Node& operator=(const Node& node_to_copy) 
    // {
    //     if (this != &node_to_copy) 
    //     {
    //         this->row = node_to_copy.row;
    //         this->col = node_to_copy.col;
    //         this->g = node_to_copy.g;
    //         this->h = node_to_copy.h;
    //         this->f = node_to_copy.f;

    //         // Perform a deep copy of the parent node
    //         if(node_to_copy.parent != nullptr) 
    //         {
    //             this->parent = new Node(*node_to_copy.parent); // Perform a deep copy of the parent
    //         } 
    //         else 
    //         {
    //             this->parent = nullptr;
    //         }
    //     }

    //     return *this;
    // }

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

#endif