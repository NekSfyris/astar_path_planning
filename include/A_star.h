#ifndef ASTAR_H
#define ASTAR_H

#include<iostream>

#include "Grid.h"
#include "Cell.h"
#include "utils.h"

#include <vector>

using namespace std;


class AStar {
public:
    AStar(Grid* grid);
    void initPlanner(const Cell& start, const Cell& goal); // initialize planner
    bool step(const Cell& goal); // do one step of the A*
    std::vector<Cell> getPath() const; // get the inal path if we found it
    
    //this cost is typically determined by factors like terrain, movement cost, or other considerations specific to the application or map
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