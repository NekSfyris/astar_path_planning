#ifndef ASTAR_H
#define ASTAR_H

#include<iostream>

#include "Grid.h"
#include "Cell.h"

#include <vector>

using namespace std;



// Define a structure to represent nodes
struct Node 
{
    int row;            // node's row position
    int col;            // node's col position
    int g;              // cost from the start node to this node
    int h;              // heuristic (estimated cost to goal)
    int f;              // total cost = g + h
    Node* parent;       // parent node
};

class AStar {
public:
    AStar(Grid* grid);
    void initPlanner(const Cell& start, const Cell& goal); // initialize planner
    bool step(const Cell& goal); // do one step of the A*
    std::vector<Cell> getPath() const; // get the inal path if we found it
    int calcCostEuclidean(const Node& current, const Node& neighbor); // calculate Euclidean distance/cost between two nodes
    int calcCostManhattan(const Node& current, const Node& neighbor); // calculate Manhattan distance/cost between two nodes

private:
    Grid* grid; // pointer to the grid containing the map
    std::vector<Node> openList; // nodes to be evaluated
    std::vector<Node> closedList; // evaluated nodes
    std::vector<Cell> path_to_goal; // final path
    bool pathFound; // flag to identify path found
};

#endif