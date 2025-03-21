#pragma once
#include<vector>
#include<iostream>
#include"Graph_types.h"
#include <boost/graph/graph_traits.hpp>
#include"PathFinder.h"
class GraphHandler {
public:


	//顶点对
	std::vector<VertexPair> vertexPairs;
	//顶点对对应的路径，一一对应
	std::vector<std::vector<std::vector<int>>> vertexPairsPath;

	Graph graph;
	// 定义顶点 id 映射
	VertexIdMap vertexMap;
	// 定义边 id 映射
	EdgeIdMap edgeMap;
	GraphHandler() {
		//添加id与描述符的映射，根据id标识符可以直接找到对应顶点或边，提高查找效率,不用每次查找都是遍历
		// 添加顶点
		addVertex({ 5 });
		addVertex({ 4 });
		addVertex({ 3 });
		addVertex({ 2 });
		addVertex({ 1 });
		addVertex({ 0 });
		addEdge(0, 1, { 8, 5.0f });
		addEdge(0, 2, { 1, 1.0f });
		addEdge(1, 3, { 7, 1.0f });
		addEdge(2, 3, { 3, 1.0f });
		addEdge(2, 4, { 4, 1.0f });
		addEdge(3, 5, { 6, 1.0f });
		addEdge(4, 5, { 9, 5.0f });
		addVertexPair({ 0,1,1.0f });
		addVertexPair({ 4,5,1.0f });

	}
	//// 你也可以为构造函数添加其他参数，进行更加灵活的初始化
	GraphHandler(const std::vector<VertexPair>& pairs, const Graph& g_data) : vertexPairs(pairs), graph(g_data) {}
	void preHandle();
private:
	// 添加顶点
	void addVertex(VertexProperties v);
	// 添加边
	void addEdge(int id1, int id2, EdgeProperties e);
	//添加节点对
	void addVertexPair(VertexPair pair);

};
