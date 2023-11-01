#ifndef ASTAR_H
#define ASTAR_H

#include<iostream>

#include "Grid.h"
#include "Cell.h"

#include <vector>

using namespace std;



// Define a structure to represent nodes
struct Node {
    int row, col;           // Node's position
    int g;              // Cost from the start node to this node
    int h;              // Heuristic (estimated cost to goal)
    Node* parent;       // Parent node
};

class AStar {
public:
    AStar(Grid* grid);
    bool findPath(const Cell& start, const Cell& goal); // Find the path
    bool step(); // Perform one step of the algorithm
    std::vector<Cell> getPath() const; // Get the path when it's found

private:
    Grid* grid; // Pointer to the grid containing the map
    std::vector<Node> openList; // Nodes to be evaluated
    std::vector<Node> closedList; // Evaluated nodes
    std::vector<Cell> path; // Final path
    bool pathFound; // Flag to track path found
};

#endif