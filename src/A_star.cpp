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
    Node startNode = {start.row, start.col, 0, 0, 0, nullptr};
    Node goalNode = {goal.row, goal.col, 0, 0, 0, nullptr};

    // add the initial node to the open list
    int g = 0;
    int h = calcHeuristicEuclidean(startNode, goalNode);
    int f = g + h;
    Node initNode = {startNode.row, startNode.col, g, h, f, nullptr};
    openList.push_back(initNode);

    //TEST
    TESTcurrNode = new Node{startNode.row, startNode.col, 0, 0, 0, nullptr};
    TESTopenList.push_back(initNode);

    // update state
    astarState = EXPLORING;

}

void AStar::step(const Cell& goal)
{

    cout << "****************************** Current step: " << step_counter << endl;

    if(last_node.parent!=nullptr && step_counter>0)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~last_node~ row="<< last_node.row<<", col=" << last_node.col << ", parent_row=" << last_node.parent->row << ", parent_col="<< last_node.parent->col<< endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    // if(openList[7].parent!=nullptr && step_counter>0)
    // {
    //     cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //     cout << "~currNode~ size of openList: " << openList.size() << endl;
    //     cout << "~currNode~ row="<< openList[7].row<<", col=" << openList[7].col << ", parent_row=" << openList[7].parent->row << ", parent_col="<< openList[7].parent->col<< endl;
    //     cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    // }

    // Cell objects to Node objects
    Node goalNode = {goal.row, goal.col, 0, 0, 0, nullptr};

    // TEST - if no path found
    if(TESTopenList.empty()) 
    {
        astarState = NO_PATH;
        cout << "TESTopenList - NO_PATH" << endl;
        return;
    }

    // if no path found
    if(openList.empty()) 
    {
        astarState = NO_PATH;

        return;
    }




    // initialize "lowest score" node
    int minCostF = openList[0].f;
    int minCostH = openList[0].h;
    int minCostG = openList[0].g;
    int minIndex = 0;



    // find the next node with the lowest score (considering f, h, and g)
    for(int i = 1; i < openList.size(); i++) 
    {
        // find the node with the lowest f score
        if(openList[i].f < minCostF) 
        {
            minCostF = openList[i].f;
            minCostH = openList[i].h;
            minCostG = openList[i].g;
            minIndex = i;
        }
        else if(openList[i].f == minCostF)
        {
            // in case they have the same f score, solve the tie with the h score
            if(openList[i].h < minCostH)
            {
                minCostF = openList[i].f;
                minCostH = openList[i].h;
                minCostG = openList[i].g;
                minIndex = i;
            }
            else if(openList[i].h == minCostH)
            {
                // in case they have the same f score and h score, solve the tie with the g score
                if(openList[i].g < minCostG)
                {
                    minCostF = openList[i].f;
                    minCostH = openList[i].h;
                    minCostG = openList[i].g;
                    minIndex = i;
                }                
            }
        }
    }



    // if(step_counter ==0)
    // {        
    //     // get new current node
    // currNode = openList[0];}
    //     else{
    //      // get new current node
    // currNode = openList[7];
    //     }

    // Node currNode(openList[minIndex]);

    currNode_ptr = &openList[minIndex];

    if(step_counter>0)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "TEST ~currNode_ptr~ row="<< currNode_ptr->row<<", col=" << currNode_ptr->col << ", parent_row=" << currNode_ptr->parent->row << ", parent_col="<< currNode_ptr->parent->col<< endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    if(step_counter>0)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "TEST ~currNode_ptr~ row="<< currNode_ptr->row<<", col=" << currNode_ptr->col << ", parent_row=" << currNode_ptr->parent->row << ", parent_col="<< currNode_ptr->parent->col<< endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }


    // if current node is the goal node, then we found the path
    // if(currNode == goalNode)
    // if(currNode.row == goal.row && currNode.col == goal.col) 
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


        //this returns the parent and current node in reverse
        cout << "last_node row="<< last_node.row<<", col=" << last_node.col<< ", parent_row="<<last_node.parent->row << ", parent_col="<< last_node.parent->col<< endl;
        //this returns the same parent x, y as the current node
        cout << "currNode row="<< currNode.row<<", col=" << currNode.col<< ", parent_row="<<currNode.parent->row << ", parent_col="<< currNode.parent->col<< endl;
        cout << "goal_node row="<< goal_node.row<<", col=" << goal_node.col<< ", parent_row="<<goal_node.parent->row << ", parent_col="<< goal_node.parent->col<< endl;


        // Goal reached, reconstruct the path
        // Node* node = &goal_node;
        // cout << endl << "RUNNING THE WHILE LOOP! --------------------" << endl;
        // while(node != nullptr && node->parent != nullptr) 
        // {

        //     cout << "row="<< node->row<<", col=" << node->col<< ", parent_row="<<node->parent->row << ", parent_col="<< node->parent->col<< endl;
        //     path_to_goal.insert(path_to_goal.begin(), Cell(node->row, node->col, grid->getNumRows(), grid->getNumColumns()));
        //     node = node->parent;
        // }
        // cout << "--------------------------------------------" << endl;



        astarState = PATH_FOUND;

        return;
    }

    //IF THIS LINE GETS EXECUTED BEFORE THE CHECK "if we are to goal node", then the currNode_ptr prints the same parent and child x,y
    currNode = openList[minIndex];

    //TEST
    TESTcurrNode = &openList[minIndex];

    if(step_counter>0)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "TEST ~currNode_ptr~ row="<< currNode_ptr->row<<", col=" << currNode_ptr->col << ", parent_row=" << currNode_ptr->parent->row << ", parent_col="<< currNode_ptr->parent->col<< endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }





    if(currNode.parent!=nullptr)
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~currNode~ minIndex selected: " << minIndex << endl;
        cout << "~currNode~ row="<< currNode.row<<", col=" << currNode.col << ", parent_row=" << currNode.parent->row << ", parent_col="<< currNode.parent->col<< endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }
    else
    {
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "~currNode~ row="<< currNode.row<<", col=" << currNode.col << endl;
        cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    }

    // remove previous node from the open list
    openList.erase(openList.begin() + minIndex);

    //TEST
    TESTopenList.erase(TESTopenList.begin() + minIndex);

    // add current node to the closed list
    closedList.push_back(currNode);




    // get neighbors of the current node
    std::vector<Node> neighbors = grid->getNeighborCells(currNode);

    // find the next "lowest" cost neighbor
    for(Node& neighbor : neighbors) 
    {

        // if neighbor is in the closed list then skip it
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
        int tentative_g_cost = currNode.g + calcCostEuclidean(currNode, neighbor);

        // check if neighbor is in the open list
        bool inOpenList = false;
        for(Node& openNode : openList) 
        {
            if(openNode == neighbor)
            // if(openNode.row == neighbor.row && openNode.col == neighbor.col)
            {
                cout << "TEST1!!!!!!!!!!"<< endl;
                inOpenList = true;
                if(tentative_g_cost < openNode.g)
                {
                    openNode.g = tentative_g_cost;
                    openNode.h = calcHeuristicEuclidean(openNode, goalNode);
                    openNode.f = openNode.g + openNode.h;
                    openNode.parent = &currNode;
                    cout << "TEST111111111111111111111111111111111111111111111111!!!!!!!!!!"<< endl;
                    cout << "row="<< openNode.row<<", col=" << openNode.col<< ", parent_row="<<openNode.parent->row << ", parent_col="<< openNode.parent->col<< endl;
                }
                break;
            }
        }

        // if neighbor is not in open list, add it
        if(!inOpenList)
        {
            // cout << "TEST2!!!!!!!!!!"<< endl;
            neighbor.g = tentative_g_cost;
            neighbor.h = calcHeuristicEuclidean(neighbor, goalNode);
            neighbor.f = neighbor.g + neighbor.h;
            neighbor.parent = &currNode;
            openList.push_back(neighbor);
            cout << "NOT_IN_OPENLIST row="<< neighbor.row<<", col=" << neighbor.col<< ", parent_row="<<neighbor.parent->row << ", parent_col="<< neighbor.parent->col<< ", f_cost="<< neighbor.f<< endl;
        }
    }

    // store the last saved node with lowest score
    last_node = currNode;
    // if(last_node.parent!=nullptr)
    // {
    //     cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //     cout << "~last_node~ row="<< last_node.row<<", col=" << last_node.col << ", parent_row=" << last_node.parent->row << ", parent_col="<< last_node.parent->col<< endl;
    //     cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    // }
    // else
    // {
    //     cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    //     cout << "~last_node~ row="<< last_node.row<<", col=" << last_node.col << endl;
    //     cout << "~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    // }

    step_counter++;

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

std::vector<Cell> AStar::getPath()
{

    cout << "---------------------------------------------------" << endl;
    cout << "Generating path!"<< endl;
    cout << "row="<< goal_node.row<<"col=" << goal_node.col<< "parent_row="<<goal_node.parent->row << "parent_col="<< goal_node.parent->col<< endl;

    // Goal reached, reconstruct the path
    Node* node = &goal_node;

    while(node != nullptr) 
    {
        cout << "row="<< node->row<<", col=" << node->col<< ", parent_row="<<node->parent->row << ", parent_col="<< node->parent->col<< endl;
        path_to_goal.insert(path_to_goal.begin(), Cell(node->row, node->col, grid->getNumRows(), grid->getNumColumns()));
        node = node->parent;
    }

    return path_to_goal;
}

