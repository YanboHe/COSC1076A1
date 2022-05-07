
#include "PathPlanner.h"

#include <iostream>

// Initialise with a given Env of size (rows,cols)
PathPlanner::PathPlanner(Env env, int rows, int cols){
   this->rows = rows;
   this->cols = cols;

    for (int i=0; i<rows; i++) {
        for (int j=0; j<cols; j++) {
            this->env[i][j] = env[i][j];
        }
    }
}

PathPlanner::~PathPlanner(){
   
}

// Set The initial position
void PathPlanner::initialPosition(int row, int col){
   //Node* node = new Node(row,col,0);

}


NodeList* PathPlanner::getReachableNodes(){
    //Construct a node list
    NodeList* openList = new NodeList();

    //find Starting point
    for (int i=0; i<ENV_DIM; i++){
        for (int j=0; j<ENV_DIM; j++){
            if (env[i][j] == SYMBOL_START){
                //construct starting point
                Node* node = new Node(i,j,0);
                //add to list
                openList->addBack(node);
            }
        }
    }

    //create closed list
    NodeList* closedList = new NodeList();

    //define a variable p pointing to the start node in open list
    Node* p = openList->get(0);

    int row =0;
    int col =0;
    bool flag = false;
    int distance = 0;
    while(!flag){
        row = p->getRow();
        col = p->getCol();
        distance = p->getDistanceToS();
        distance+=1;
        
        for (int direction=0; direction<4; direction++){
            //get current direction
            if (direction==0){
                //up
                if (env[row-1][col] != SYMBOL_WALL){
                    Node* q = new Node(row-1,col,distance);
                    if (!openList->containsNode(q)){
                        openList->addBack(q);
                    } else {
                        delete q;
                    }
                }
            } else if(direction==1){
                //right
                if (env[row][col+1] != SYMBOL_WALL){
                    Node* q = new Node(row,col+1,distance);
                    if (!openList->containsNode(q)){
                        openList->addBack(q);
                    } else {
                        delete q;
                    }
                }
            } else if(direction==2){
                //down
                if (env[row+1][col] != SYMBOL_WALL){
                    Node* q = new Node(row+1,col,distance);
                    if (!openList->containsNode(q)){
                        openList->addBack(q);
                    } else {
                        delete q;
                    }
                }
            } else if(direction==3){
                //left
                if (env[row][col-1] != SYMBOL_WALL){
                    Node* q = new Node(row,col-1,distance);
                    if (!openList->containsNode(q)){
                        openList->addBack(q);
                    } else {
                        delete q;
                    }
                }
            }
        }

        //Add p to closed-list C.
        closedList->addBack(p);

        //Select a node form open list that is not in closed list
        int index=0;
        bool notInList = false;
        while(!notInList){  ;
            bool match = closedList->containsNode(openList->get(index));   
            if (!match){
                p = openList->get(index);
                notInList = true;
            } else if (index >= openList->getLength()-1){
                flag = true;
                notInList = true;
            } else {
                index++;
            }
        }
        if (p == nullptr){
            flag = true;
        }
    }

    NodeList* reachableNodes = new NodeList(*closedList);

    closedList->~NodeList();
    openList->~NodeList();
    p = nullptr;

    return reachableNodes;
    
}



NodeList* PathPlanner::getPath(){

    //apply reachable node list
    NodeList* reachableNode =getReachableNodes();

    
    //Construct a node list
    NodeList* pathList = new NodeList();
    
    int row=0;
    int col=0;
    //find the Goal point
    for (int i=0; i<ENV_DIM; i++){
        for (int j=0; j<ENV_DIM; j++){
            if (env[i][j] == SYMBOL_GOAL){
                //find node object
                row = i;
                col = j;
            }
        }
    }
    //Find the goal point
    int index=0;
    bool found=false;
    while(!found && index < reachableNode->getLength()){
        if (reachableNode->get(index)->getCol()==col &&
            reachableNode->get(index)->getRow()==row){
                //construct goal point
                Node* node = new Node(row,col,reachableNode->get(index)->getDistanceToS());
                //add to list
                pathList->addBack(node);
                found = true;
        }
        index++;
    }

    //define a variable p pointing to the goal node
    Node* p = pathList->get(0);
    
    int distance = p->getDistanceToS();
    bool flag = false;

    //special case
    if (reachableNode->getLength()==2) {
        flag = true;
    } 
    
    while(!flag){

        row = p->getRow();
        col = p->getCol();
        
        //Find 4 neighbour nodes
        int i=0;
        bool found = false;

        while(!found) {
            
            if (reachableNode->get(i)->getCol()==col &&
                reachableNode->get(i)->getRow()==(row-1) &&
                reachableNode->get(i)->getDistanceToS() == (distance-1)) {
                    p = reachableNode->get(i);
                    found=true;
            } else if ( reachableNode->get(i)->getCol()==(col+1) &&
                        reachableNode->get(i)->getRow()==row && 
                        reachableNode->get(i)->getDistanceToS() == (distance-1)){
                            p = reachableNode->get(i);
                            found=true;
            } else if ( reachableNode->get(i)->getCol()==col &&
                        reachableNode->get(i)->getRow()==(row+1) && 
                        reachableNode->get(i)->getDistanceToS() == (distance-1)) {
                            p = reachableNode->get(i);
                            found=true;
            }else if (reachableNode->get(i)->getCol()==(col-1) &&
                        reachableNode->get(i)->getRow()==row && 
                        reachableNode->get(i)->getDistanceToS() == (distance-1)){
                            p = reachableNode->get(i);
                            found=true;
            }
            i++;
            
        }
        //store path in list
        pathList->addBack(p);
        distance = p->getDistanceToS();
        if (distance ==0) {
            flag =true;
        }
    }
    //Reverse path array
    NodeList* pathListStraight = new NodeList();
    for (int i=pathList->getLength()-1; i>-1; i--){
        pathListStraight->addBack(pathList->get(i));
    }

    //DEEP copy
    NodeList* solution = new NodeList(*pathListStraight);
    pathListStraight->~NodeList();
    pathList->~NodeList();
    p = nullptr;
    return solution;

}
