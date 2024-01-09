#ifndef ASTAR_H
#define ASTAR_H

#include<iostream>
#include <cmath>
#include <map>
#include <vector>
#include <memory>

#include "Grid.h"
#include "Cell.h"
#include "utils.h"

using namespace std;


class AStar {
public:

    std::vector<Cell> getPath(); // get the final path if we found it
    
    AStar(Grid* grid);
    void initPlanner(const Cell& start, const Cell& goal); // initialize planner
    void step(const Cell& goal); // do one step of the A*
    
    // this cost is typically determined by factors like terrain, movement cost, or other considerations specific to the application or map
    int calcCostEuclidean(const Node& current, const Node& neighbor); // calculate Euclidean distance/cost between two nodes
    int calcCostEuclidean(const Node* current, const Node& neighbor); // calculate Euclidean distance/cost between two nodes
    int calcCostEuclidean(const Node* current, const Node* neighbor); // calculate Euclidean distance/cost between two nodes
    int calcCostManhattan(const Node& current, const Node& neighbor); // calculate Manhattan distance/cost between two nodes
    int calcCostEuclidean(std::shared_ptr<Node> current, const Node& neighbor); // calculate Manhattan distance/cost between two nodes

    // the Heuristic cost typically involves distance metrics like the Manhattan distance or Euclidean distance from the current node to the goal one
    int calcHeuristicEuclidean(const Node& current, const Node* goal); // calculate Euclidean distance/cost between two nodes
    int calcHeuristicEuclidean(const Node* current, const Node* goal); // calculate Euclidean distance/cost between two nodes
    int calcHeuristicManhattan(const Node& current, const Node& goal); // calculate Manhattan distance/cost between two nodes
    int calcHeuristicEuclidean(std::shared_ptr<Node> current, std::shared_ptr<Node> goal); // calculate Euclidean distance/cost between two nodes
    int calcHeuristicEuclidean(const Node& current, std::shared_ptr<Node> goal); // calculate Euclidean distance/cost between two nodes

    //lists of Nodes for the planner
    std::vector<std::shared_ptr<Node>> openList;
    std::vector<std::shared_ptr<Node>> closedList;

    std::shared_ptr<Node> currNode_ptr = nullptr;

    // initial state of the A* 
    PlannerState astarState = INIT;

    // map of planner output states with messages
    map <PlannerState, string> planner_output = {
        {INIT, "PLANNER INITIALIZED!"}, 
        {EXPLORING, "EXPLORING MAP!"}, 
        {NO_PATH, "NO PATH AVAILABLE TO GOAL! TERMINAING!"}, 
        {PATH_FOUND, "PATH WAS FOUND!"},
        {FINISH, "PATH PLANNING FINISHED! KEEP PLOTTING THE MAP!"}
    };


private:
    Grid* grid; // pointer to the 2D grid
    std::vector<Cell> path_to_goal; // final path
    std::shared_ptr<Node> goalNode_ptr; // node for the goal grid cell
    int step_counter; // how many steps the planner has ran
};

#endif