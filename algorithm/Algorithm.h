#pragma once
#include"GraphHandler.h"
#include<fstream>
#include<boost/graph/graphviz.hpp>
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
	void write_graphviz_with_paths(std::ostream& os, const std::vector<std::vector<int>>& selected_paths) {
		std::set<int> highlighted_edges;
		for (const auto& path : selected_paths) {
			for (int edge_id : path) {
				highlighted_edges.insert(edge_id);
			}
		}

		// 顶点写入器：通过 id 查找顶点描述符并访问属性
		auto vertex_writer = [&](std::ostream& os, int vertex_id) {
			if (graphHandler.vertexMap.find(vertex_id) != graphHandler.vertexMap.end()) {
				VertexDescriptor v = graphHandler.vertexMap[vertex_id];
				os << "[label=\"" << graphHandler.graph[v].id << "\", pos=\"" << graphHandler.graph[v].x << "," << graphHandler.graph[v].y << "!\"]";
			}
		};

		// 边写入器：通过 id 查找边描述符并访问属性
		auto edge_writer = [&](std::ostream& os, int edge_id) {
			if (graphHandler.edgeMap.find(edge_id) != graphHandler.edgeMap.end()) {
				EdgeDescriptor e = graphHandler.edgeMap[edge_id];
				if (highlighted_edges.count(edge_id)) {
					os << "[color=red, penwidth=3.0]";
				}
				else {
					os << "[color=gray]";
				}
			}
		};

		// 自定义图写入函数
		os << "graph G {\n";

		// 写入顶点
		for (const auto& [vertex_id, vertex_descriptor] : graphHandler.vertexMap) {
			os << "  " << vertex_id << " ";
			vertex_writer(os, vertex_id);
			os << ";\n";
		}

		// 写入边
		for (const auto& [edge_id, edge_descriptor] : graphHandler.edgeMap) {
			VertexDescriptor source = boost::source(edge_descriptor, graphHandler.graph);
			VertexDescriptor target = boost::target(edge_descriptor, graphHandler.graph);
			os << "  " << graphHandler.graph[source].id << " -- " << graphHandler.graph[target].id << " ";
			edge_writer(os, edge_id);
			os << ";\n";
		}

		os << "}\n";
	}

	void visualizeGraphWithPaths(const std::vector<std::vector<int>>& selected_paths) {
		std::ofstream dot_file("graph_with_paths.dot");
		write_graphviz_with_paths(dot_file, selected_paths);
		dot_file.close();
		system("dot -Tpng graph_with_paths.dot -o graph.png");
	}
};
