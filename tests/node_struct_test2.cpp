// THIS TEST IS A SOLUTION TO THE node_struct_test.cpp TEST FILE

#include <iostream>
#include <vector>
#include <memory>

using namespace std;


struct Node {
    int row;            // node's row position
    int col;            // node's col position
    int g;              // cost from the start node to this node
    int h;              // heuristic (estimated cost to goal)
    int f;              // total cost = g + h
    std::shared_ptr<Node> parent;       // parent node

    Node(int r, int c, int costG, int costH, std::shared_ptr<Node> parentNode = nullptr)
        : row(r), col(c), g(costG), h(costH), f(costG + costH), parent(parentNode) {}
};


// print all node attributes
void printNode(std::shared_ptr<Node> node)
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

void printVector(std::vector<std::shared_ptr<Node>> openListPtr)
{
    std::cout << "************************* PRINTING Vector ********************************" << std::endl;
    for(int i=0; i<openListPtr.size(); i++)
    {
        std::shared_ptr<Node> TESTcurrNode = openListPtr[i];

        printNode(TESTcurrNode);
    }
    std::cout << "****************************************************************" << std::endl;
}



int main() 
{
    std::vector<std::shared_ptr<Node>> openListPtr;

    std::shared_ptr<Node> temp_node;



    // std::vector<std::shared_ptr<Node>> nodes;

    // // Create Node 1 and Node 2 with the parent-child relationship
    // std::shared_ptr<Node> node1 = std::make_shared<Node>(0, 0, 5, 10, nullptr);
    // std::shared_ptr<Node> node2 = std::make_shared<Node>(1, 1, 8, 12, node1);

    // nodes.push_back(node1);
    // nodes.push_back(node2);

    

    // Instantiate and push node1 into openList
    if(true) 
    {
        std::shared_ptr<Node> node1, node2;
        node1 = std::make_shared<Node>(1, 1, 0, 0, nullptr);
        openListPtr.push_back(node1);

        node2 = std::make_shared<Node>(2, 2, 1, 1, node1);
        openListPtr.push_back(node2);

        node1 = std::make_shared<Node>(3, 3, 2, 2, node2);
        openListPtr.push_back(node1);

        temp_node = node1;

        // delete node1; // Remember to free the allocated memory if necessary. BY NOT DELETING, WHEN LATER I PRINT THE NODE NUMBER 3, IT GIVES ME THE CORRECT PARENT. IF I DELETE IT GIVES ME THE SAME PARENT AS THE CHILD 
    }

    // Assign TESTcurrNode to a specific index in openList in a different if block
    int indexToAssign = 1; // Change this to the index you want to assign to TESTcurrNode
    if (indexToAssign >= 0 && indexToAssign < openListPtr.size()) {
        std::shared_ptr<Node> TESTcurrNode = openListPtr[indexToAssign];
        std::cout << "TESTcurrNode assigned to index " << indexToAssign << " in openList." << " Child_row= " << TESTcurrNode->row << ", parent_row= " << TESTcurrNode->parent->row << std::endl;

    } else {
        std::cout << "Index to assign for TESTcurrNode is out of bounds." << std::endl;
    }

    std::cout << "Size of list: " << openListPtr.size() << std::endl;

    // Re-instantiate node1 with different values
    std::shared_ptr<Node> node1 = std::make_shared<Node>(4, 4, 3, 3, temp_node);
    openListPtr.push_back(node1);

    // Assign TESTcurrNode to point to the new node1
    int indexForNewNode1 = openListPtr.size() - 1;
    if (indexForNewNode1 >= 0 && indexForNewNode1 < openListPtr.size()) {
        std::shared_ptr<Node> TESTcurrNode = openListPtr[indexForNewNode1];
        std::cout << "TESTcurrNode assigned to index " << indexForNewNode1 << " in openList." << " Child_row= " << TESTcurrNode->row << ", parent_row= " << TESTcurrNode->parent->row << std::endl;

        // ... (Perform operations with TESTcurrNode pointing to the new node1 if needed)
    } else {
        std::cout << "Index to assign for TESTcurrNode (new node1) is out of bounds." << std::endl;
    }

    std::cout << "Size of list: " << openListPtr.size() << std::endl;



    printVector(openListPtr);

    // Accessing information using classical for-loop
    // for (int i = 0; i < openListPtr.size(); ++i) 
    // {
    //     std::cout << "Node - Row: " << openListPtr[i]->row << ", Col: " << openListPtr[i]->col << ", Parent: ";
    //     if (openListPtr[i]->parent)
    //         std::cout << "(" << openListPtr[i]->parent->row << ", " << openListPtr[i]->parent->col << ")";
    //     std::cout << std::endl;
    // }


    // all nodes to have the first one as parent
    std::shared_ptr<Node> firstNode = openListPtr[0];
    int original_size = openListPtr.size();
    for(int i=0; i<original_size; i++)
    {
        std::shared_ptr<Node> TESTcurrNode = openListPtr[i];
        if(i!=0)
        {
            TESTcurrNode->parent = firstNode;
            
            std::shared_ptr<Node> tempNode;
            tempNode = std::make_shared<Node>(10+i, 10+i, 5+i, 5+i, firstNode);
            openListPtr.push_back(tempNode); // up to here things WORK
        }
    }


    std::shared_ptr<Node> lastNode = openListPtr[openListPtr.size() -1];
    std::shared_ptr<Node> tempNode = std::make_shared<Node>(10, 10, 5, 5, lastNode);
    openListPtr.push_back(tempNode);


    printVector(openListPtr);


    return 0;
}


