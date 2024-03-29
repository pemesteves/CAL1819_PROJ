/*
 * citySightseeing.h
 */

#ifndef SRC_CITYSIGHTSEEING_H_
#define SRC_CITYSIGHTSEEING_H_

#include <vector>
#include <utility>

#include "VertexInfo.h"
#include "Graph.h"
#include "Person.h"

std::vector<VertexInfo> dijkstraShortestRoute(Graph graph, VertexInfo start, std::vector<VertexInfo> pois, VertexInfo finish);

std::vector<std::pair<std::vector<unsigned long>, std::vector<Person>>> dividePeople(std::vector<Person> people, std::vector<unsigned long> pois, int bus_capacity);

#endif /* SRC_CITYSIGHTSEEING_H_ */
