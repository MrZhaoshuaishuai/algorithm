#include"PathFinder.h"
#include <boost/graph/graph_traits.hpp>

void PathFinder::dfs(
	const Graph& g,
	Graph::vertex_descriptor current,
	Graph::vertex_descriptor target,
	std::vector<int>& path,
	std::set<Graph::vertex_descriptor>& visited,
	std::vector<std::vector<int>>& result
) {
	//如果当前顶点就是目标顶点则说明路径找到了
	if (current == target) {
		result.push_back(path);
		return;
	}

	auto out_edges = boost::out_edges(current, g);
	auto ei = out_edges.first;
	auto ei_end = out_edges.second;
	for (; ei != ei_end; ++ei) {
		Graph::vertex_descriptor next = boost::target(*ei, g);
		if (visited.find(next) != visited.end()) continue;

		int edge_id = g[*ei].id;
		visited.insert(next);
		path.push_back(edge_id);

		dfs(g, next, target, path, visited, result);

		path.pop_back();
		visited.erase(next);
	}
}

std::vector<std::vector<int>> PathFinder::find_all_paths(
	const Graph& g,
	Graph::vertex_descriptor s,
	Graph::vertex_descriptor t
) {
	std::vector<std::vector<int>> result;
	std::set<Graph::vertex_descriptor> visited{ s };
	std::vector<int> path;
	dfs(g, s, t, path, visited, result);
	return result;
}
