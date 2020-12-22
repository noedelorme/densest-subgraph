#ifndef GRAPH_INCLUDED
#define GRAPH_INCLUDED

#include <iostream>
#include <string>
#include <unordered_map>
#include <fstream>

#include "Node.h"

class Graph{
private:
    std::string name{};
    std::string fileName{};
    int n{};
    int m{};
    int minDegree{};
    int maxDegree{};
    float density{};
    float bestDensity{};
    Node* weakestNode{};
    std::unordered_map<int,Node*> nodes{};
    std::unordered_map<int,Node*> data{};
    Node* dot;

public:
    //Constructors
    Graph();
    Graph(std::string _name, std::string _fileName);

    //Getters
    std::string getName() const;
    std::string getFileName() const;
    int getN() const;
    int getM() const;
    int getMinDegree() const;
    int getMaxDegree() const;
    float getDensity() const;
    float getBestDensity() const;

    void test() const;

    //Method used to turn file into data structure
    void fromFile();
    //Method used to turn data structure into file
    void toFile();

    //Method used to find the weakest node given a starting degree
    Node* findWeakestNode(int degree);

    //Method used to apply a iteration
    void subgraphize();
    //Method used to compute the densest subgraph
    float densestSubgraph();

    //Method used to display the graph
    void display(std::ostream& s) const;
};

#endif // GRAPH_INCLUDED