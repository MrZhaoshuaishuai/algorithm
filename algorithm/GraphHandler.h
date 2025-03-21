#pragma once
#include<vector>
#include<iostream>
#include"Graph_types.h"
#include <boost/graph/graph_traits.hpp>
#include"PathFinder.h"
class GraphHandler {
public:


	//�����
	std::vector<VertexPair> vertexPairs;
	//����Զ�Ӧ��·����һһ��Ӧ
	std::vector<std::vector<std::vector<int>>> vertexPairsPath;

	Graph graph;
	// ���嶥�� id ӳ��
	VertexIdMap vertexMap;
	// ����� id ӳ��
	EdgeIdMap edgeMap;
	GraphHandler() {
		//���id����������ӳ�䣬����id��ʶ������ֱ���ҵ���Ӧ�����ߣ���߲���Ч��,����ÿ�β��Ҷ��Ǳ���
		// ��Ӷ���
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
	//// ��Ҳ����Ϊ���캯������������������и������ĳ�ʼ��
	GraphHandler(const std::vector<VertexPair>& pairs, const Graph& g_data) : vertexPairs(pairs), graph(g_data) {}
	void preHandle();
private:
	// ��Ӷ���
	void addVertex(VertexProperties v);
	// ��ӱ�
	void addEdge(int id1, int id2, EdgeProperties e);
	//��ӽڵ��
	void addVertexPair(VertexPair pair);

};
