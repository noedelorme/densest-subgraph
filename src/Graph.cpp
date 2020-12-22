#include "./headers/Graph.h"

Graph::Graph(std::string _name, std::string _fileName){
	name = _name;
	fileName = _fileName;
	n=0;
	m=0;
	minDegree=0;
	maxDegree=0;
	density=0;
	bestDensity=0;
	dot = new Node(-1,-1);

	fromFile();
}

std::string Graph::getName() const{ return name; }
std::string Graph::getFileName() const{ return fileName; }
int Graph::getN() const{ return n; }
int Graph::getM() const{ return m; }
int Graph::getMinDegree() const{ return minDegree; }
int Graph::getMaxDegree() const{ return maxDegree; }
float Graph::getDensity() const{ return density; }
float Graph::getBestDensity() const{ return bestDensity; }

void Graph::test() const{
	for(auto& x: nodes){
		Node* node = x.second;
		if(node->getDegree() != node->getNeighbors().size()){
			std::cout << node->getId() << std::endl;
		}
		
	}
}

void Graph::fromFile(){
	//Create nodes and set neighborhood by reading the file
	std::ifstream file(fileName);
	std::string line;
	if(file){
		while(getline(file, line)){
			int s = line.find(" ");
			int fromId = std::stoi(line.substr(0,s));
			int toId = std::stoi(line.substr(s+1,-1));

			if(fromId != toId){	
				if(nodes.find(fromId) == nodes.end()){
					nodes[fromId] = new Node(fromId, 0);
					n++;
				}
				if(nodes.find(toId) == nodes.end()){
					nodes[toId] = new Node(toId, 0);
					n++;
				}

				if(!nodes[fromId]->isNeighbor(nodes[toId])){
					nodes[fromId]->addNeighbor(nodes[toId]);
					nodes[fromId]->incrDegree();
					nodes[toId]->addNeighbor(nodes[fromId]);
					nodes[toId]->incrDegree();
					m++;
				}
			}
		}
	}else{
		std::cout << "Couldn't read file." << std::endl;
	}

	//Set density and bestDensity
	density = ((float)m)/((float)n);
	bestDensity = density;

	//Fill data
	minDegree = std::min(n,m);
	maxDegree = 0;
	for(auto& x: nodes){
		Node* node = x.second;
		int degree = node->getDegree();
		if(degree < minDegree){
			minDegree = degree;
			weakestNode = node;
		}
		if(degree > maxDegree){
			maxDegree = degree;
		}

		if(data.find(degree) == data.end()){
			data[degree] = node;
			node->setPredecessor(dot);
			node->setSuccessor(dot);
		}else{
			data[degree]->setPredecessor(node);
			node->setSuccessor(data[degree]);
			node->setPredecessor(dot);
			data[degree] = node;
		}
    }

	//Create empty data degree
	for(int degree=0; degree<maxDegree+1; degree++){
		if(data.find(degree) == data.end()){
			data[degree] = dot;
		}
    }
}

void Graph::toFile(){
	std::cout << "Not implemented yet." << std::endl;
}

Node* Graph::findWeakestNode(int degree){
	int currentDegree = degree;
	Node* newWeakestNode;
	bool weakestNodeFound = false;
	while(!weakestNodeFound){
		if(data[currentDegree]->getId() != -1){
			newWeakestNode = data[currentDegree];
			weakestNodeFound = true;
		}else{
			currentDegree++;
		}
	}
	return newWeakestNode;
}

void Graph::subgraphize(){
	//Delete the weakest node from data
	weakestNode->remove();
	if(weakestNode->getPredecessor()->getId()==-1){
		data[weakestNode->getDegree()] = weakestNode->getSuccessor();
		data[weakestNode->getDegree()]->setPredecessor(dot);
	}else{
		weakestNode->remove();
	}

	Node* copyWeakestNode = weakestNode; //To save the graph if densest
	n--;
	
	if(weakestNode->getDegree()>0){
		std::unordered_map<int,Node*> neighbors = weakestNode->getNeighbors();
		
		Node* weakestNeighbor;
		bool firstWeakestNeighborFound = false;
		for(auto& x : weakestNode->getNeighbors()){
			Node* neighbor = x.second;

			//Remove an edge
			m--;
			//Update neighbor neighborhood
			neighbor->removeNeighbor(weakestNode);
			//Remove neighbor from data
			if(neighbor->getPredecessor()->getId()==-1){
				data[neighbor->getDegree()] = neighbor->getSuccessor();
				data[neighbor->getDegree()]->setPredecessor(dot);
			}else{
				neighbor->remove();
			}
			//Decrement degree of neighbor
			neighbor->decrDegree();
			//Add neighbor to data
			data[neighbor->getDegree()]->setPredecessor(neighbor);
			neighbor->setSuccessor(data[neighbor->getDegree()]);
			neighbor->setPredecessor(dot);
			data[neighbor->getDegree()] = neighbor;
			
			if(firstWeakestNeighborFound){
				if(neighbor->getDegree() < weakestNeighbor->getDegree()){
					weakestNeighbor = neighbor;
				}
			}else{
				weakestNeighbor = neighbor;
				firstWeakestNeighborFound = true;
			}
		}

		if(weakestNeighbor->getDegree() <= minDegree){
			minDegree = weakestNeighbor->getDegree();
			weakestNode = weakestNeighbor;
		}else{
			weakestNode = findWeakestNode(minDegree);
			minDegree = weakestNode->getDegree();
		}
	}else{
		weakestNode = findWeakestNode(minDegree);
		minDegree = weakestNode->getDegree();
	}
	

	//Compute the new density
	density = ((float)m)/((float)n);

	//Save the current graph if it is densest
	if(density>bestDensity){
		bestDensity = density;
		copyWeakestNode->noElite();
	}
}

float Graph::densestSubgraph(){
	while(m>0){
		subgraphize();
		//std::cout << "n: " << n << " ; m: " << m  <<std::endl;
		//weakestNode->display(std::cout);
	}

	return bestDensity;
}

void Graph::display(std::ostream& s) const{
	for(auto& x: data){
		Node* node = x.second;
		int degree = x.first;
		std::cout << "--=Group " << degree << "=--" << std::endl;
		while(node->getId()!=-1){
			node->display(std::cout);
			node = node->getSuccessor();
		}
    }
}