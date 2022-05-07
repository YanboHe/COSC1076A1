/*
 * For the approach that I took for this assignment,
 * I strickly followed the Assignment Spec guidlines.
 * I first implmented the definition of Node class, then NodeList class and PathPlanner class.
 * I had a lot of problems when implementing the constructors for each classes.
 * It was mainly becuase the given declaration do not have any parameters to pass in, 
 * which forced me to code in a different way which I would not. 
 * However, this is a good experience for future working environment. 
 * 
 */


#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Helper test functions
void testNode();
void testNodeList();
void printNode(Node* node);

// Read a environment from standard input.
void readEnvStdin(Env env);

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution);


int main(int argc, char** argv){
    // THESE ARE SOME EXAMPLE FUNCTIONS TO HELP TEST YOUR CODE
    // AS YOU WORK ON MILESTONE 2. YOU CAN UPDATE THEM YOURSELF
    // AS YOU GO ALONG.
    // COMMENT THESE OUT BEFORE YOU SUBMIT!!!

    // std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    // testNode();
    // testNodeList();
    // std::cout << "DONE TESTING" << std::endl << std::endl;

    // Load Environment 
    Env env;
    readEnvStdin(env);

    
    // Solve using forwardSearch
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 2
    PathPlanner* pathplanner = new PathPlanner(env, ENV_DIM, ENV_DIM);
    std::cout << "create new path planner" << std::endl;
    NodeList* reachablePositions = nullptr;
    std::cout << "setting reachable positions to null" << std::endl;
    reachablePositions = pathplanner->getReachableNodes();
    std::cout << "get reachable nodes" << std::endl;


    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();

    //print the path
    printPath(env, solution);

    delete pathplanner;
    delete reachablePositions;
    delete solution;

}
// TESTING - print node
void printNode(Node* node) {
    std::cout << "row: " << node->getRow()
              << " col: " << node->getCol()
              << " distanceToS: " << node->getDistanceToS() 
              << std::endl;
}

void readEnvStdin(Env env){
    //TODO - read environment from a file
    int envRead = 0;
    while(!std::cin.eof() && envRead <= (ENV_DIM*ENV_DIM)) {
        
        for (int i=0; i<ENV_DIM; i++) {
            for (int j=0; j<ENV_DIM; j++) {
                std::cin >> env[i][j];
            }
        }
    }

    // //Print maze environment:
    // std::cout << "Maze environment:" << std::endl;
    // for (int i=0; i<ENV_DIM; i++) {
    //     for (int j=0; j<ENV_DIM; j++) {
    //         std::cout << env[i][j];
    //     }
    //     std::cout << std::endl;
    // }
    
}

void printPath(Env env, NodeList* solution) {
    //TODO
    Node* p = solution->get(2);

    for (int i=1; i<solution->getLength(); i++){
        int row = solution->get(i)->getRow();
        int col = solution->get(i)->getCol();
        //get directions
        if (p->getRow() == row +1 && 
            p->getCol() == col) {
                env[row+1][col]= '^';
        } else if (p->getRow() == row && 
            p->getCol() == col-1) {
                env[row][col-1]= '>';
        } else if (p->getRow() == row -1 && 
            p->getCol() == col) {
                env[row-1][col]= 'v';
        } else if (p->getRow() == row && 
            p->getCol() == col+1) {
                env[row][col+1]= '<';
        }
        p = solution->get(i);
    }

    //Print path:
    for (int i=0; i<ENV_DIM; i++) {
        for (int j=0; j<ENV_DIM; j++) {
            std::cout << env[i][j];
        }
        std::cout << std::endl;
    }
}

void printReachablePositions(Env env, NodeList* reachablePositions){
    //TODO
}

void testNode() {
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node* node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceToS() << std::endl;
    delete node;
}

void testNodeList() {
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList* nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node* b1 = new Node(1, 1, 1);
    nodeList->addBack(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node* b2 = new Node(0, 0, 1);
    nodeList->addBack(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node* getB = nodeList->get(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceToS() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}