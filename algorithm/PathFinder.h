#pragma once
#include <vector>
#include <set>
#include"Graph_types.h"

class PathFinder {
public:
	// 查找所有从s到t的无环路径
	static std::vector<std::vector<int>> find_all_paths(
		const Graph& g,
		Graph::vertex_descriptor s,
		Graph::vertex_descriptor t
	);

private:
	static void dfs(
		const Graph& g,
		Graph::vertex_descriptor current,
		Graph::vertex_descriptor target,
		std::vector<int>& path,
		std::set<Graph::vertex_descriptor>& visited,
		std::vector<std::vector<int>>& result
	);
};