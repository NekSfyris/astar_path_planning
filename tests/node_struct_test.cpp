#include <iostream>
#include <vector>

struct Node {
    int row;            // node's row position
    int col;            // node's col position
    int g;              // cost from the start node to this node
    int h;              // heuristic (estimated cost to goal)
    int f;              // total cost = g + h
    Node* parent;       // parent node
};

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

        // delete node1; // Remember to free the allocated memory if necessary
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
        std::cout << "TESTcurrNode assigned to index " << indexForNewNode1 << " in openList for new node1." << std::endl;

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

    delete node1; // Remember to free the allocated memory if necessary

    return 0;
}