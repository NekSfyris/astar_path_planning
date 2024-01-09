#include <iostream>
#include <vector>

using namespace std;

// Some links explaining why i have the below problem with pointers and parent data:
// - https://stackoverflow.com/questions/67839175/c-values-of-pointers-are-wrong-after-return
// - https://stackoverflow.com/questions/7464372/pointer-problem-using-vector-containing-structs?rq=3

struct Node {
    int row;            // node's row position
    int col;            // node's col position
    int g;              // cost from the start node to this node
    int h;              // heuristic (estimated cost to goal)
    int f;              // total cost = g + h
    Node* parent;       // parent node
};


// print all node attributes
void printNode(Node* node)
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

void printList(std::vector<Node> openList)
{
    std::cout << "************************* PRINTING LIST ********************************" << std::endl;
    for(int i=0; i<openList.size(); i++)
    {
        Node* TESTcurrNode = &openList[i];

        printNode(TESTcurrNode);

    }
    std::cout << "****************************************************************" << std::endl;
}



int main() {
    std::vector<Node> openList;

    Node* temp_node;

    // Instantiate and push node1 into openList
    if (true) {
        Node* node1;
        node1 = new Node{1, 1, 0, 0, 0, nullptr};
        openList.push_back(*node1);

        node1 = new Node{2, 2, 1, 1, 1, node1};
        openList.push_back(*node1);
        // ... (Perform operations with node1 if needed)

        node1 = new Node{3,3, 2,2,2, node1};
        openList.push_back(*node1);

        temp_node = node1;

        // delete node1; // Remember to free the allocated memory if necessary. BY NOT DELETING, WHEN LATER I PRINT THE NODE NUMBER 3, IT GIVES ME THE CORRECT PARENT. IF I DELETE IT GIVES ME THE SAME PARENT AS THE CHILD 
    }

    // Assign TESTcurrNode to a specific index in openList in a different if block
    int indexToAssign = 1; // Change this to the index you want to assign to TESTcurrNode
    if (indexToAssign >= 0 && indexToAssign < openList.size()) {
        Node* TESTcurrNode = &openList[indexToAssign];
        std::cout << "TESTcurrNode assigned to index " << indexToAssign << " in openList." << " Child_row= " << TESTcurrNode->row << ", parent_row= " << TESTcurrNode->parent->row << std::endl;

        // ... (Perform operations with TESTcurrNode if needed)
    } else {
        std::cout << "Index to assign for TESTcurrNode is out of bounds." << std::endl;
    }

    std::cout << "Size of list: " << openList.size() << std::endl;

    // Re-instantiate node1 with different values
    Node* node1 = new Node{4,4, 3,3,3, temp_node};
    openList.push_back(*node1);

    // Assign TESTcurrNode to point to the new node1
    int indexForNewNode1 = openList.size() - 1;
    if (indexForNewNode1 >= 0 && indexForNewNode1 < openList.size()) {
        Node* TESTcurrNode = &openList[indexForNewNode1];
        std::cout << "TESTcurrNode assigned to index " << indexForNewNode1 << " in openList." << " Child_row= " << TESTcurrNode->row << ", parent_row= " << TESTcurrNode->parent->row << std::endl;

        // ... (Perform operations with TESTcurrNode pointing to the new node1 if needed)
    } else {
        std::cout << "Index to assign for TESTcurrNode (new node1) is out of bounds." << std::endl;
    }

    std::cout << "Size of list: " << openList.size() << std::endl;


    // Assign TESTcurrNode to a specific index in openList in a different if block
    indexToAssign = 2; // Change this to the index you want to assign to TESTcurrNode
    if (indexToAssign >= 0 && indexToAssign < openList.size()) {
        Node* TESTcurrNode = &openList[indexToAssign];
        std::cout << "TESTcurrNode assigned to index " << indexToAssign << " in openList." << " Child_row= " << TESTcurrNode->row << ", parent_row= " << TESTcurrNode->parent->row << std::endl;

        // ... (Perform operations with TESTcurrNode if needed)
    } else {
        std::cout << "Index to assign for TESTcurrNode is out of bounds." << std::endl;
    }


    // Assign TESTcurrNode to a specific index in openList in a different if block
    indexToAssign = 3; // Change this to the index you want to assign to TESTcurrNode
    if (indexToAssign >= 0 && indexToAssign < openList.size()) {
        Node* TESTcurrNode = &openList[indexToAssign];
        std::cout << "TEST" << std::endl;
        std::cout << "TESTcurrNode assigned to index " << indexToAssign << " in openList." << " Child_row= " << TESTcurrNode->row << ", parent_row= " << TESTcurrNode->parent->row << std::endl;

        // ... (Perform operations with TESTcurrNode if needed)
    } else {
        std::cout << "Index to assign for TESTcurrNode is out of bounds." << std::endl;
    }


    std::cout << "Size of list: " << openList.size() << std::endl;


    // Assign TESTcurrNode to a specific index in openList in a different if block
    indexToAssign = 2; // Change this to the index you want to assign to TESTcurrNode
    if (indexToAssign >= 0 && indexToAssign < openList.size()) {
        Node* TESTcurrNode = &openList[indexToAssign];
        std::cout << "TESTcurrNode assigned to index " << indexToAssign << " in openList." << " Child_row= " << TESTcurrNode->row << ", parent_row= " << TESTcurrNode->parent->row << std::endl;

        // ... (Perform operations with TESTcurrNode if needed)
    } else {
        std::cout << "Index to assign for TESTcurrNode is out of bounds." << std::endl;
    }




    //print list
    printList(openList);

    // IF I DO THIS CODE HERE THEN EVERYTHING LOOKS GOOD AT THE END. IF I DO THIS AFTER THE FOR THOUGH, IT IS WRONG
    // Node* node2 = new Node{10, 10, 5, 5, 5, node1};
    // openList.push_back(*node2);


    // all nodes to have the first one as parent
    Node* firstNode = &openList[0];
    int original_size = openList.size();
    // for(int i=0; i<original_size; i++)
    // {
    //     Node* TESTcurrNode = &openList[i];
    //     if(i!=0)
    //     {
    //         TESTcurrNode->parent = firstNode;
            
    //         // Node* tempNode = new Node{10+i, 10+i, 5, 5, 5, firstNode};
    //         // openList.push_back(*tempNode);// THIS MAKES THE PARENT TO BE PRINTED COMPLETELY WRONG
    //     }
    // }

    // THIS ALSO MAKES THE PARENT TO BE PRINTED COMPLETELY WRONG FOR ALL NODES. THE PROBLEM IS THAT I ASSIGN AS PARENT THE FIRST NODE
    // Node* tempNode = new Node{10, 10, 5, 5, 5, firstNode};
    // openList.push_back(*tempNode);

    // THIS MAKES THE LAST ONE LOOK GOOD BUT ALL THE PREVIOUS ONES TO HAVE WRONG PARENT. IF THE lastNode IS ANY OTHER NODE OTHER THAN THE FIRST, THEN THE PARENT IS CORRECT, OTHERWISE WRONG
    // Node* lastNode = &openList[openList.size()-1];
    // Node* tempNode = new Node{10, 10, 5, 5, 5, lastNode};
    // openList.push_back(*tempNode);

    // THIS ALSO MAKES THE LAST ONE LOOK GOOD BUT ALL THE PREVIOUS ONES TO HAVE WRONG PARENT
    // Node* node2 = new Node{10, 10, 5, 5, 5, node1};
    // openList.push_back(*node2);

    //print list
    printList(openList);







    delete node1; // Remember to free the allocated memory if necessary

    return 0;
}


