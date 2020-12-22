#include <iostream>
#include <string>
#include <chrono>
#include <unordered_map>

#include "./headers/Graph.h"
#include "./headers/Node.h"

using namespace std::chrono; 

int main(int argc, const char* argv[]){
	Graph* G = new Graph("graph", "./examples/facebook.txt");

	int n = G->getN();
	int m = G->getM();

	auto start = high_resolution_clock::now();

	G->densestSubgraph();

	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);

	std::cout << "Graph: " << G->getFileName() << std::endl;
	std::cout << "Nodes: " << n << std::endl;
	std::cout << "Edges: " << m << std::endl;
	std::cout << "Maximum density: " << G->getBestDensity() << std::endl;
	std::cout << "Execution time: " << duration.count() << " microseconds" << std::endl;

	return 0;
}