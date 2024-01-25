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

    // initialize step counter of the planner
    step_counter = 0;

    // Cell objects to Node objects
    std::shared_ptr<Node> startNode = std::make_shared<Node>(start.row, start.col, 0, 0, nullptr);
    std::shared_ptr<Node> goalNode = std::make_shared<Node>(goal.row, goal.col, 0, 0, nullptr);
    
    // add the initial node to the open list
    int g = 0;
    int h = calcHeuristicEuclidean(startNode, goalNode);
    std::shared_ptr<Node> initNode = std::make_shared<Node>(startNode->row, startNode->col, g, h, nullptr);
    openList.push_back(initNode);

    // update state
    astarState = EXPLORING;

}

void AStar::step(const Cell& goal)
{

    cout << "*********************************************************** Current step: " << step_counter << endl;

    // Cell object to Node objects
    std::shared_ptr<Node> goalNode = std::make_shared<Node>(goal.row, goal.col, 0, 0, nullptr);

    // if no path found
    if(openList.empty()) 
    {
        astarState = NO_PATH;

        return;
    }


    // initialize "lowest score" node
    int minCostF = openList[0]->f;
    int minCostH = openList[0]->h;
    int minCostG = openList[0]->g;
    int minIndex = 0;


    // find the next node with the lowest score (considering f, h, and g)
    for(int i = 1; i < openList.size(); i++) 
    {
        // find the node with the lowest f score
        if(openList[i]->f < minCostF) 
        {
            minCostF = openList[i]->f;
            minCostH = openList[i]->h;
            minCostG = openList[i]->g;
            minIndex = i;
        }
        else if(openList[i]->f == minCostF)
        {
            // in case they have the same f score, solve the tie with the h score
            if(openList[i]->h < minCostH)
            {
                minCostF = openList[i]->f;
                minCostH = openList[i]->h;
                minCostG = openList[i]->g;
                minIndex = i;
            }
            else if(openList[i]->h == minCostH)
            {
                // in case they have the same f score and h score, solve the tie with the g score
                if(openList[i]->g < minCostG)
                {
                    minCostF = openList[i]->f;
                    minCostH = openList[i]->h;
                    minCostG = openList[i]->g;
                    minIndex = i;
                }                
            }
        }
    }



    currNode_ptr = openList[minIndex];

    //printNode(currNode_ptr);


    // if current node is the goal node, then we found the path
    // if(currNode == goalNode)
    if(currNode_ptr->row == goal.row && currNode_ptr->col == goal.col) 
    {

        //THIS RETURNS WRONG PARENT AND CURRENT NODE X, Y
        // goal_node = last_node; // set the goal node as the current node
        // goal_node.parent = last_node.parent;

        //THIS RETURNS THE SAME PARENT AND CHILD
        goalNode_ptr = currNode_ptr;

        if(step_counter>0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "TEST ~goalNode_ptr~ row="<< goalNode_ptr->row<<", col=" << goalNode_ptr->col << ", parent_row=" << goalNode_ptr->parent->row << ", parent_col="<< goalNode_ptr->parent->col << ", f_cost="<< goalNode_ptr->f << ", h_cost_to_goal="<< goalNode_ptr->h<< endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }

        //THIS RETURNS THE SAME PARENT AND CHILD
        if(step_counter>0)
        {
            cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
            cout << "TEST ~currNode_ptr~ row="<< currNode_ptr->row<<", col=" << currNode_ptr->col << ", parent_row=" << currNode_ptr->parent->row << ", parent_col="<< currNode_ptr->parent->col<< endl;
            cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        }


        astarState = PATH_FOUND;

        return;
    }

    // remove previous node from the open list
    openList.erase(openList.begin() + minIndex);

    // add current node to the closed list
    closedList.push_back(currNode_ptr);



    // get neighbors of the current node
    std::vector<Node> neighbors = grid->getNeighborCells(currNode_ptr);

    // find the next "lowest" cost neighbor // for(Node& neighbor : neighbors)
    for(int i=0; i < neighbors.size(); i++)
    {
        // Node* neighbor = &neighbors[i];
        Node neighbor = neighbors[i];
        std::shared_ptr<Node> neighborNode = std::make_shared<Node>(neighbor.row, neighbor.col, neighbor.g, neighbor.h, neighbor.parent);

        // if neighbor is in the closed list then skip it
        bool foundInClosedList = false;
        // for(const Node& closedNode : closedList)
        for(int j=0; j < closedList.size(); j++)
        {
            std::shared_ptr<Node> closedNode = closedList[j];
            // if (neighbor == closedNode)
            if(neighbor.row == closedNode->row && neighbor.col == closedNode->col)
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
    
        // compute tentative g cost. Represents the cost to reach the neighbor through our current node
        int tentative_g_cost = currNode_ptr->g + calcCostEuclidean(currNode_ptr, neighbor);

        // check if neighbor is in the open list
        bool inOpenList = false;
        int open_index = -1;
        for(int j=0; j < openList.size(); j++) 
        {
            std::shared_ptr<Node> openNeighborNode = openList[j];

            // if(openNeighborNode == neighbor)
            if(openNeighborNode->row == neighbor.row && openNeighborNode->col == neighbor.col)
            {
                // cout << "NODE IS IN OPENLIST!!!!!!!!!!"<< endl;
                inOpenList = true;
                open_index = j;
                // if(tentative_g_cost < openNeighborNode->g)
                // {
                //     openNeighborNode->g = tentative_g_cost;
                //     openNeighborNode->h = calcHeuristicEuclidean(openNeighborNode, goalNode);
                //     openNeighborNode->f = openNeighborNode->g + openNeighborNode->h;
                //     openNeighborNode->parent = currNode_ptr;
                //     cout << "TEST111111111111111111111111111!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
                //     printNode(openNeighborNode);
                // }
                break;
            }
        }

        // check if neighbor is in the closed list
        int closed_index = -1;
        for(int j=0; j < closedList.size(); j++) 
        {
            std::shared_ptr<Node> closedNeighborNode = closedList[j];

            if(closedNeighborNode->row == neighbor.row && closedNeighborNode->col == neighbor.col)
            {
                closed_index = j;
                break;
            }
        }


        if(closed_index==-1 && open_index==-1) // if NOT in open and NOT in closed list
        {
            std::shared_ptr<Node> tempCurrNode_ptr;
            tempCurrNode_ptr = std::make_shared<Node>(neighbor.row, neighbor.col, tentative_g_cost, calcHeuristicEuclidean(neighbor, goalNode), currNode_ptr);
            openList.push_back(tempCurrNode_ptr);            
        }
        else if(open_index!=-1) //|| closed_index!=-1) // if in open list
        {
            if(tentative_g_cost < openList[open_index]->g)
            {
                openList[open_index]->g = tentative_g_cost;
                openList[open_index]->h = calcHeuristicEuclidean(openList[open_index], goalNode);
                openList[open_index]->f = openList[open_index]->g + openList[open_index]->h;
                openList[open_index]->parent = currNode_ptr;
            }
        }
        else if(closed_index!=-1) // if in closed list
        {
            if(tentative_g_cost < closedList[closed_index]->g)
            {
                closedList[closed_index]->g = tentative_g_cost;
                closedList[closed_index]->h = calcHeuristicEuclidean(closedList[closed_index], goalNode);
                closedList[closed_index]->f = closedList[closed_index]->g + closedList[closed_index]->h;
                closedList[closed_index]->parent = currNode_ptr;
            
                // // add to the recursive list
                // recurseVisitedNeighbors.push_back(currNode_ptr);
                // recurseVisitedNeighbors.push_back(closedList[closed_index]);

                // // update the neighbors of the neighbors for the shortest path. curr_iter is 0
                // recurseUpdateList(closedList[closed_index], 0);

                //update each neighbor
                std::vector<Node> new_neighbors = grid->getNeighborCells(closedList[closed_index]);
                for(int i=0; i < new_neighbors.size(); i++)
                {
                    Node new_neighbor = new_neighbors[i];

                    // compute tentative g cost. Represents the cost to reach the neighbor through our current node
                    int new_tentative_g_cost = closedList[closed_index]->g + calcCostEuclidean(closedList[closed_index], new_neighbor);

                    if(new_tentative_g_cost < new_neighbor.g)
                    {
                        new_neighbor.g = new_tentative_g_cost;
                        new_neighbor.parent = closedList[closed_index];
                    }
                }

            }
        }




        // // if neighbor is not in open list, add it
        // if(!inOpenList)
        // {
        //     std::shared_ptr<Node> tempCrecurseNeighborListurrNode_ptr;
        //     // printNode(currNode_ptr);
        //     tempCurrNode_ptr = std::make_shared<Node>(neighbor.row, neighbor.col, tentative_g_cost, calcHeuristicEuclidean(neighbor, goalNode), currNode_ptr);
        //     //this change kind of makes it work better sometimes but not really also
        //     //tempCurrNode_ptr = std::make_shared<Node>(neighbor.row, neighbor.col, calcCostEuclidean(currNode_ptr, neighbor), calcHeuristicEuclidean(neighbor, goalNode), currNode_ptr);
        //     openList.push_back(tempCurrNode_ptr);

        //     cout << "NOT_IN_OPENLIST row="<< tempCurrNode_ptr->row<<", col=" << tempCurrNode_ptr->col<< ", parent_row="<<tempCurrNode_ptr->parent->row << ", parent_col="<< tempCurrNode_ptr->parent->col<< ", f_cost="<< tempCurrNode_ptr->f<< endl;
        // }
    }

    step_counter++;
}


// void AStar::recurseUpdateList(std::shared_ptr<Node> current, int curr_iter)
// {

//     // break the recursive function if we have reached the max iterations allowed
//     if(curr_iter >= max_iter_recursive_list)
//         return;

//     //update each neighbor
//     std::vector<Node> new_neighbors = grid->getNeighborCells(current);
//     for(int i=0; i < new_neighbors.size(); i++)
//     {
//         Node new_neighbor = new_neighbors[i];

//         // compute tentative g cost. Represents the cost to reach the neighbor through our current node
//         int new_tentative_g_cost = closedList[closed_index]->g + calcCostEuclidean(closedList[closed_index], new_neighbor);

//         if(new_tentative_g_cost < new_neighbor.g)
//         {
//             new_neighbor.g = new_tentative_g_cost;
//             new_neighbor.parent = closedList[closed_index];

//             // check if neighbor is in the closed list
//             int closed_index = -1;
//             for(int j=0; j < closedList.size(); j++) 
//             {
//                 std::shared_ptr<Node> closedNeighborNode = closedList[j];

//                 if(closedNeighborNode->row == neighbor.row && closedNeighborNode->col == neighbor.col)
//                 {
//                     closed_index = j;
//                     break;
//                 }
//             }

//             if()
//                 recurseUpdateList(, curr_iter++)
//         }
//     }
// }


// int AStar::calcCostEuclidean(std::shared_ptr<Node> current, const Node& neighbor)
// {
//     // Euclidean distance between current and neighbor node
//     int dx = neighbor.row - current->row;
//     int dy = neighbor.col - current->col;
    
//     int cost = std::sqrt(dx * dx + dy * dy);
//     cost *= 10; // just for simplicity in numbers

//     return cost;
// }

// int AStar::calcCostManhattan(const Node& current, const Node& neighbor)
// {
//     // Manhattan distance (sum of absolute differences in x and y)
//     int dx = std::abs(neighbor.row - current.row);
//     int dy = std::abs(neighbor.col - current.col);

//     int cost = dx + dy;
//     cost *= 10; // just for simplicity in numbers

//     return cost;
// }

// int AStar::calcHeuristicEuclidean(std::shared_ptr<Node> current, std::shared_ptr<Node> goal)
// {
//     // Euclidean distance between current and neighbor node
//     int dx = goal->row - current->row;
//     int dy = goal->col - current->col;
    
//     int cost = std::sqrt(dx * dx + dy * dy);
//     cost *= 10; // just for simplicity in numbers

//     return cost;
// }

// int AStar::calcHeuristicEuclidean(const Node& current, std::shared_ptr<Node> goal)
// {
//     // Euclidean distance between current and neighbor node
//     int dx = goal->row - current.row;
//     int dy = goal->col - current.col;
    
//     int cost = std::sqrt(dx * dx + dy * dy);
//     cost *= 10; // just for simplicity in numbers

//     return cost;
// }

// int AStar::calcHeuristicManhattan(const Node& current, const Node& goal)
// {
//     // Manhattan distance (sum of absolute differences in x and y)
//     int dx = std::abs(goal.row - current.row);
//     int dy = std::abs(goal.col - current.col);

//     int cost = dx + dy;
//     cost *= 10; // just for simplicity in numbers

//     return cost;
// }

std::vector<Cell> AStar::getPath()
{

    cout << "---------------------------------------------------" << endl;
    cout << "Generating path!"<< endl;

    // Goal reached, reconstruct the path
    std::shared_ptr<Node> node = goalNode_ptr;

    while(node != nullptr) 
    {
        printNode(node);
        path_to_goal.insert(path_to_goal.begin(), Cell(node->row, node->col, grid->getNumRows(), grid->getNumColumns()));
        node = node->parent;
    }

    return path_to_goal;
}

