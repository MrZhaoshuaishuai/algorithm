#include "GraphHandler.h"
#include<set>

#pragma once

void GraphHandler::preHandle()
{
	for (VertexPair pair : vertexPairs) {
		PathFinder pf;
		std::vector<std::vector<int>> vec = pf.find_all_paths(graph, vertexMap[pair.v1Id], vertexMap[pair.v2Id]);
		vertexPairsPath.push_back(vec);
	}
	//for (size_t i = 0; i < vertexPairsPath.size(); ++i) {
	//	for (size_t j = 0; j < vertexPairsPath[i].size(); ++j) {
	//		for (size_t k = 0; k < vertexPairsPath[i][j].size(); ++k) {
	//			std::cout << "vertexPairsPath[" << i << "][" << j << "][" << k << "] = " << vertexPairsPath[i][j][k] << std::endl;
	//		}
	//	}
	//}
}


void GraphHandler::addVertex(VertexProperties v)
{
	if (vertexMap.find(v.id) != vertexMap.end()) {
		throw std::invalid_argument("点已经存在");
	}
	auto vertex = boost::add_vertex(v, graph);
	vertexMap[v.id] = vertex;
}

void GraphHandler::addEdge(int id1, int id2, EdgeProperties e)
{
	if (vertexMap.find(id1) == vertexMap.end() || vertexMap.find(id2) == vertexMap.end()) {
		throw std::invalid_argument("不存在该点");
	}
	if (edgeMap.find(e.id) != edgeMap.end()) {
		throw std::invalid_argument("边已存在");
	}
	auto v1 = vertexMap[id1];
	auto v2 = vertexMap[id2];
	auto edge = boost::add_edge(v1, v2, e, graph).first;
	edgeMap[e.id] = edge;  // 使用e.id作为键来存储边
}

void GraphHandler::addVertexPair(VertexPair pair)
{
	vertexPairs.push_back(pair);
}

