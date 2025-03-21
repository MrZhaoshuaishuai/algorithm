#pragma once
#include"GraphHandler.h"
class Algorithm {
	//结果
public:
	float total_cost = FLT_MAX;
	std::vector<std::vector<int>> selected_paths;
	GraphHandler graphHandler;
	Algorithm() {
	}
	Algorithm(GraphHandler graphHandler) {
		this->graphHandler = graphHandler;
	}
	void printRes()
	{
		std::cout << "最少代价为：" << this->total_cost << std::endl;
		for (int i = 0; i < selected_paths.size(); i++) {
			std::cout << "顶点" << graphHandler.vertexPairs[i].v1Id << "和顶点" << graphHandler.vertexPairs[i].v2Id << "经过的边有：";
			for (int j = 0; j < selected_paths[i].size(); j++) {
				if (j == selected_paths[i].size() - 1) std::cout << graphHandler.graph[graphHandler.edgeMap[selected_paths[i][j]]].id;
				else std::cout << graphHandler.graph[graphHandler.edgeMap[selected_paths[i][j]]].id << "-";
			}
			std::cout << std::endl;
		}
	}
	float computeCost(std::vector<std::vector<int>> selection) {
		float cost = 0.0f;
		//用来存储经过的边
		std::set<int> s;
		for (int i = 0; i < selection.size(); i++) {
			std::vector<int> path = selection[i];
			float w = graphHandler.vertexPairs[i].val;
			for (int j : path) {
				s.insert(j);
				float len = graphHandler.graph[graphHandler.edgeMap[j]].length;
				cost += len * w;
			}
		}
		for (int i : s) {
			float len = graphHandler.graph[graphHandler.edgeMap[i]].length;
			float c = graphHandler.graph[graphHandler.edgeMap[i]].val;
			cost += len * c;
		}
		return cost;
	}
	void visualization() {

	}
};
