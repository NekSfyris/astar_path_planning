#ifndef ASTAR_H
#define ASTAR_H

#include<iostream>

#include "Grid.h"
#include "Cell.h"

#include <vector>

using namespace std;



// Define a structure to represent nodes
struct Node {
    int row;            // Node's row position
    int col;            // Node's col position
    int g;              // Cost from the start node to this node
    int h;              // Heuristic (estimated cost to goal)
    int f;              // total cost = g + h
    Node* parent;       // Parent node
};

class AStar {
public:
    AStar(Grid* grid);
    void initPlanning(const Cell& start, const Cell& goal); // Find the path
    bool step(); // Perform one step of the algorithm
    std::vector<Cell> getPath() const; // Get the path when it's found

private:
    Grid* grid; // Pointer to the grid containing the map
    std::vector<Node> openList; // Nodes to be evaluated
    std::vector<Node> closedList; // Evaluated nodes
    std::vector<Cell> path_to_goal; // Final path
    bool pathFound; // Flag to track path found
};

#endif