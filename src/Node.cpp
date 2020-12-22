#include "./headers/Node.h"

Node::Node(int _id, int _degree){
    id = _id;
    degree = _degree;
    elite = true;
}

int Node::getId() const{ return id; }
int Node::getDegree() const{ return degree; }
bool Node::isElite() const{ return elite; }
Node* Node::getPredecessor() const{ return predecessor; }
Node* Node::getSuccessor() const{ return successor; }
std::unordered_map<int,Node*> Node::getNeighbors() const{ return neighbors; }

void Node::noElite(){ elite=false; }

void Node::setPredecessor(Node* node){ predecessor=node; }
void Node::setSuccessor(Node* node){ successor=node; }
void Node::remove(){
    predecessor->setSuccessor(successor);
    successor->setPredecessor(predecessor);
}

bool Node::isNeighbor(Node* node) const{
    if(neighbors.find(node->getId())==neighbors.end()){
        return false;
    }else{
        return true;
    }
}

void Node::incrDegree(){ degree++; }
void Node::decrDegree(){ degree--; }

void Node::addNeighbor(Node* node){ neighbors[node->getId()] = node; }
void Node::removeNeighbor(Node* node){ neighbors.erase(node->getId()); }

void Node::display(std::ostream& s) const{
    s << "Node " << id << " (" << degree << " neighbors)";
    s << " (" << predecessor->getId() << ";" << successor->getId() << ")" << std::endl;
}