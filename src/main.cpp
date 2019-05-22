#include "Graph.h"
#include "map.h"
#include "MutablePriorityQueue.h"
#include "VertexInfo.h"

#include <iostream>
#include <string>

using namespace std;

int main(){
	cout << "City: ";
	string city;
	cin >> city;
	Graph graph = readGraph(city);
	graph.SCC();

	viewGraph(graph);
	getchar();
	return 0;
}
