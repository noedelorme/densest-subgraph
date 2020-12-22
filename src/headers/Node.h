#ifndef NODE_INCLUDED
#define NODE_INCLUDED

#include <iostream>
#include <unordered_map>

class Node{
private:
    int id{};
    int degree{};
    bool elite{};
    Node* predecessor{};
    Node* successor{};
    std::unordered_map<int,Node*> neighbors{};

public:
    //Constructors
    Node();
    Node(int _id, int _degree);

    //Getters
    int getId() const;
    int getDegree() const;
    bool isElite() const;
    Node* getPredecessor() const;
    Node* getSuccessor() const;
    std::unordered_map<int,Node*> getNeighbors() const;

    //Setters
    void noElite();

    //Methods used to manage predecessor/sucessor
    void setPredecessor(Node* node);
    void setSuccessor(Node* node);
    void remove();

    //Method used to check if nodes are neighbors
    bool isNeighbor(Node* node) const;

    //Method used to increment/decrement degree
    void incrDegree();
    void decrDegree();

    //Methods used to add/remove a neighbor
    void addNeighbor(Node* node);
    void removeNeighbor(Node* node);

    //Method used to display the graph
    void display(std::ostream& s) const;
};

#endif // NODE_INCLUDED