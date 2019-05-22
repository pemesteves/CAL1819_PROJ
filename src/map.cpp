/**
 * map.cpp
 *
 * Defined functions of map.h header file
 */

#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <thread>
#include <vector>

#include "map.h"
#include "graphviewer.h"
#include "edgetype.h"

using namespace std;

Graph<VertexInfo> readGraph(string name){

    Graph<VertexInfo> g;

    string map_dir = "mapas/"+name+"/";
    ifstream f(map_dir+"T03_nodes_X_Y_"+name+".txt");
    ifstream f1(map_dir+"T03_nodes_lat_lon_"+name+".txt");

    int lines = 0;
    string file_line;

    getline(f, file_line);

    lines = stoi(file_line);

    getline(f1, file_line);

    unsigned long ID;
    double X, Y, lat, lon;

    //vector<thread> threads;
    time_t tempo = time(NULL);
    cout << "Begin: 0" << endl;
    while(lines > 0){
        getline(f, file_line);
        file_line = file_line.substr(1);
        ID = stoi(file_line.substr(0, file_line.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);
        X = stod(file_line.substr(0, file_line.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);
        Y = stod(file_line.substr(0, file_line.find(")")));

        getline(f1, file_line);
        file_line = file_line.substr(file_line.find(",")+1);
        lat = stod(file_line.substr(0, file_line.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);
        lon = stod(file_line.substr(0, file_line.find(")")));

        VertexInfo v(ID, X, Y, lat, lon);
        g.addVertex(v);
        //threads.push_back(thread(g.addVertex,v));

        lines--;
    }
    /*for(vector<thread>::iterator it = threads.begin(); it != threads.end(); it++){
    	(*it).join();
    }*/
    cout << "Read Nodes: " << time(NULL)-tempo << endl;
    f.close();
    f1.close();

    f.open(map_dir+"T03_edges_"+name+".txt");

    getline(f, file_line);
    lines = stoi(file_line);

    unsigned long ID_origin, ID_destiny;

    while(lines > 0){
        getline(f, file_line);
        file_line = file_line.substr(1);

        ID_origin = stoi(file_line.substr(0, file_line.find(",")));
        file_line = file_line.substr(file_line.find(",")+1);

        ID_destiny = stod(file_line.substr(0, file_line.find(")")));

        VertexInfo origin(ID_origin, 0, 0, 0, 0);
        VertexInfo destiny(ID_destiny, 0, 0, 0, 0);

        g.addEdge(origin, destiny);

        lines--;
    }

    cout << "Read Edges: " <<  time(NULL)-tempo << endl;
    f.close();

    f.open(map_dir+"T03_tags_"+name+".txt");
    getline(f, file_line);
    lines = stoi(file_line);

    int number_nodes = 0;
    string tag;

    while(lines > 0){
        getline(f, file_line);
        tag = file_line.substr(file_line.find("=")+1);

        getline(f, file_line);
        number_nodes = stoi(file_line);

        while(number_nodes > 0){
            getline(f, file_line);
            ID = stoi(file_line);
            Vertex<VertexInfo> *v = g.findVertex(VertexInfo(ID, 0, 0, 0, 0));
            VertexInfo vi = v->getInfo();
            vi.addTag(tag);
            v->setInfo(vi);
            number_nodes--;
        }

        lines--;
    }
    cout << "Finished: " << time(NULL)-tempo << endl;

    f.close();
    return g;
}

int viewGraph(Graph<VertexInfo> graph){

	GraphViewer *gv = new GraphViewer(2000, 2000, false);

	gv->createWindow(2000, 2000);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	vector<Vertex<VertexInfo>*> vertexSet = graph.getVertexSet();
	Vertex<VertexInfo>* currentVertex = new Vertex<VertexInfo>(VertexInfo(0,0,0,0,0));
	vector<Edge<VertexInfo>> currentEdges;
	int edgeID = 0;
	double offsetX = vertexSet.at(0)->getInfo().getX();
	double offsetY = vertexSet.at(0)->getInfo().getY();

	for(size_t i = 0; i < vertexSet.size(); i++){
		currentVertex = vertexSet.at(i);
		gv->addNode(currentVertex->getInfo().getID(), currentVertex->getInfo().getX()-offsetX, currentVertex->getInfo().getY()-offsetY);
		currentEdges = currentVertex->getAdjEdges();
	}

	for(size_t i = 0; i < vertexSet.size(); i++){
		currentVertex = vertexSet.at(i);
		currentEdges = currentVertex->getAdjEdges();
		for(size_t j = 0; j < currentEdges.size(); j++){
			gv->addEdge(edgeID, currentVertex->getInfo().getID(), currentEdges.at(j).getDest()->getInfo().getID(), EdgeType::UNDIRECTED);
			edgeID++;
		}
	}

	gv->rearrange();

	return 0;
}
