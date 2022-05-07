
#include "NodeList.h"
#include <iostream>



NodeList::NodeList(){
    // NodePtr nodes[NODE_LIST_ARRAY_MAX_SIZE];
    //Initialise the node list
    for (int i=0; i<NODE_LIST_ARRAY_MAX_SIZE; i++) {
       nodes[i] = nullptr;
    }
}


NodeList::~NodeList(){
    clear();
}

NodePtr NodeList::getNodes(){
    return *nodes;
}


NodeList::NodeList(NodeList& other){
    // TODO - deep copy
    // Initialise a new node list
    //NodePtr nodesCopied[NODE_LIST_ARRAY_MAX_SIZE];
    // for (int i=0; i<NODE_LIST_ARRAY_MAX_SIZE; i++) {
    //    nodesCopied[i] = nullptr;
    // }
    
    // Copy all nodes from other
    for (int i=0; i<other.getLength(); i++){
        this->addBack(other.get(i));
    }
}



// Number of items in the list
int NodeList::getLength(){
   int len = 0;
   while(nodes[len] != nullptr && len < NODE_LIST_ARRAY_MAX_SIZE) {
        len++;
    }
    return len;
}


// Get a pointer to the ith node in the node list
NodePtr NodeList::get(int i){
    return nodes[i];
}


// Add a COPY node element to the BACK of the nodelist
void NodeList::addBack(NodePtr newNode){
   bool flag = false;
   int i = 0;
   while(!flag && i<NODE_LIST_ARRAY_MAX_SIZE){
       if(nodes[i] == nullptr){
           Node* nodeCopy = new Node(*newNode);
           nodes[i] = nodeCopy;
           flag = true;
       } else {
           i++;
       }
   }
}


// Checks if the list contains a node with the same co-ordinate
//    as the given node.
bool NodeList::containsNode(NodePtr node){
    int len = getLength();
    bool flag = false;
    int i=0;
    while(!flag && i<len) {
        if (nodes[i]->getRow() == node->getRow() && nodes[i]->getCol() == node->getCol()) {
            flag = true;
        }
        i++;
   }
   return flag;
}


// Remove everything from the list
void NodeList::clear(){
    int len = getLength();
    for(int i=0; i<len; i++) {
        nodes[i]->~Node();
        delete nodes[i];
        nodes[i] = nullptr;
    }
}