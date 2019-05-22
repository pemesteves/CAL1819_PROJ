/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <stack>
#include <limits>
#include <cmath>
#include <unordered_map>

#include "MutablePriorityQueue.h"
#include "VertexInfo.h"

using namespace std;

class Edge;
class Graph;
class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

class Vertex {
	VertexInfo info;                // contents
	vector<Edge> adj;  			    // outgoing edges
	bool visited = false;          // auxiliary field
	double dist = 0;
	Vertex *path = NULL;
	int index = 0;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(Vertex *dest, double w);

public:
	Vertex(VertexInfo in);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	VertexInfo getInfo() const;
	void setInfo(const VertexInfo);
	double getDist() const;
	Vertex *getPath() const;
	vector<Edge> getAdjEdges() const;
	friend class Graph;
	friend class MutablePriorityQueue<Vertex>;
};

/********************** Edge  ****************************/


class Edge {
	Vertex * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex *d, double w);
	Vertex * getDest() const;
	friend class Graph;
	friend class Vertex;
};


/*************************** Graph  **************************/

struct idHash
{
	int operator() (const unsigned long & id) const
	{
		return id;
	}

	bool operator() (const unsigned long & id1, const unsigned long & id2) const
	{
		return id1 == id2;
	}
};

typedef unordered_map<unsigned long, int, idHash, idHash> idHashTable;

class Graph {
	vector<Vertex *> vertexSet;    // vertex set

	idHashTable ids;

	void SCCUtil(Vertex* v, int discovered[], int early[], stack<int> *stck, bool stackMember[]);

public:
	Vertex *findVertex(const VertexInfo &in) const;
	bool addVertex(const VertexInfo &in);
	bool addEdge(const VertexInfo &sourc, const VertexInfo &dest, double w);
	bool addEdge(const VertexInfo &sourc, const VertexInfo &dest);
	int getNumVertex() const;
	vector<Vertex *> getVertexSet() const;

	void SCC();

	Vertex * initSingleSource(const VertexInfo &origin);
	bool relax(Vertex *v, Vertex *w, double weight);

	// Fp05 - single source
	void dijkstraShortestPath(const VertexInfo &s);
	void dijkstraShortestPathOld(const VertexInfo &s);
	void unweightedShortestPath(const VertexInfo &s);
	void bellmanFordShortestPath(const VertexInfo &s);
	vector<VertexInfo> getPath(const VertexInfo &origin, const VertexInfo &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<VertexInfo> getfloydWarshallPath(const VertexInfo &origin, const VertexInfo &dest) const;

};


#endif /* GRAPH_H_ */
