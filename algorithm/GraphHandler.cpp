#include "GraphHandler.h"
#include<set>

#pragma once

void GraphHandler::generate(int n, int m, int k)
{
	edges.clear();
	vertexPairs.clear();

	// 处理无效输入
	if (n <= 0) return;

	// --- 处理边界情况 ---
	if (n == 1) m = 0;          // 单个顶点无法形成边
	else m = std::max(m, n - 1); // 确保边数 ≥ n-1

	// --- 生成无向连通图的边列表 ---
	UnionFind uf(n);
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> vertexDist(0, n - 1);
	std::unordered_set<std::pair<int, int>, PairHash> edgeSet;

	// 1. 生成生成树（保证连通性）
	int edgesAdded = 0;
	while (edgesAdded < n - 1) {
		int u = vertexDist(gen), v = vertexDist(gen);
		if (u == v) continue;

		// 统一存储为 u <= v 避免重复
		if (u > v) std::swap(u, v);
		if (uf.find(u) != uf.find(v)) {
			edges.emplace_back(u, v, (randomFloat() + 0.5f)*10.0f, (randomFloat()+0.5f)*10.0f);
			edgeSet.insert({ u, v });
			uf.unite(u, v);
			edgesAdded++;
		}
	}

	// 2. 随机填充剩余边（确保不重复）
	int remaining = m - (n - 1);
	int maxPossibleEdges = n * (n - 1) / 2; // 无向图最大边数
	remaining = std::min(remaining, maxPossibleEdges - (n - 1));

	while (remaining > 0) {
		int u = vertexDist(gen), v = vertexDist(gen);
		if (u == v) continue;

		if (u > v) std::swap(u, v);
		if (!edgeSet.count({ u, v })) {
			edges.emplace_back(u, v, (randomFloat() + 0.5f)*10.0f, (randomFloat() + 0.5f)*10.0f);
			edgeSet.insert({ u, v });
			remaining--;
		}
	}

	// --- 生成顶点对列表（s≠t且不重复）---
	if (n < 2 || k <= 0) return;

	// 生成所有可能的顶点对并打乱
	std::vector<std::pair<int, int>> allPairs;
	for (int s = 0; s < n; ++s) {
		for (int t = 0; t < n; ++t) {
			if (s != t) allPairs.emplace_back(s, t);
		}
	}
	std::shuffle(allPairs.begin(), allPairs.end(), gen);

	// 取前k个不重复的顶点对
	k = std::min(k, static_cast<int>(allPairs.size()));
	for (int i = 0; i < k; ++i) {
		auto[s, t] = allPairs[i];
		vertexPairs.emplace_back(s, t, randomFloat()+0.5f);
	}
}

void GraphHandler::addToGraph()
{
	//添加顶点
	std::set<int> set;
	for (auto i : this->edges) {
		int s = i.u;
		int t = i.v;
		if (set.find(s) == set.end()) {
			set.insert(s);
			addVertex({ s });
		}
		if (set.find(t) == set.end()) {
			set.insert(t);
			addVertex({ t });
		}
	}
	//添加边
	int count = 0;
	for (auto i : this->edges) {
		addEdge(i.u, i.v, { count++, i.l_e, i.w_e });
	}
}

double GraphHandler::preHandle()
{
	auto start = std::chrono::high_resolution_clock::now();
	for (VertexPair pair : vertexPairs) {
		PathFinder pf;
		std::vector<std::vector<int>> vec = pf.find_all_paths(graph, vertexMap[pair.s], vertexMap[pair.t]);
		vertexPairsPath.push_back(vec);
	}
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> duration_ms = end - start;
	std::cout << "预处理耗时：" << duration_ms.count() << "毫秒" << std::endl;
	for (size_t i = 0; i < vertexPairsPath.size(); ++i) {
		for (size_t j = 0; j < vertexPairsPath[i].size(); ++j) {
			for (size_t k = 0; k < vertexPairsPath[i][j].size(); ++k) {
				std::cout << "vertexPairsPath[" << i << "][" << j << "][" << k << "] = " << vertexPairsPath[i][j][k] << std::endl;
			}
		}
	}
	return duration_ms.count();
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
// 新增：保存数据到文件
void GraphHandler::saveToFile() {
	const std::string base_dir = "data";
	int next_num = findMaxGraphNumber(base_dir) + 1;

	// 关键修复：动态计算补零位数（至少补两位）
	int num_digits = std::max(2, (int)std::to_string(next_num).length());
	// 生成目录名和文件名
	std::ostringstream dir_oss, file_oss;
	dir_oss << base_dir << "/graph"
		<< std::setw(num_digits) << std::setfill('0') << next_num;
	file_oss << "graph_data"
		<< std::setw(num_digits) << std::setfill('0') << next_num
		<< ".txt";

	// 创建目录
	fs::path dir_path(dir_oss.str());
	fs::create_directories(dir_path);

	// 写入文件
	fs::path file_path = dir_path / file_oss.str();
	std::ofstream outfile(file_path);
	if (!outfile) {
		std::cerr << "Error writing to " << file_path << "\n";
		return;
	}

	// 数据写入
	outfile << std::fixed << std::setprecision(2);
	outfile << "# Edges: u v weight length\n";
	for (const auto& edge : edges) {
		outfile << edge.u << " " << edge.v << " "
			<< edge.w_e << " " << edge.l_e << "\n";
	}
	outfile << "\n# Vertex Pairs: s t activity\n";
	for (const auto& pair : vertexPairs) {
		outfile << pair.s << " " << pair.t << " " << pair.a_i << "\n";
	}

	// 新增：输出边信息到控制台
	std::cout << "边信息:\n";
	for (const auto& edge : edges) {
		std::cout << "Edge " << edge.u << "-" << edge.v
			<< " (w=" << edge.w_e << ", l=" << edge.l_e << ")\n";
	}

	std::cout << "数据已保存至: " << file_path << "\n";
}



int GraphHandler::findMaxGraphNumber(const std::string& base_dir) {
	int max_num = 0;

	if (!fs::exists(base_dir)) return 0;

	for (const auto& entry : fs::directory_iterator(base_dir)) {
		if (entry.is_directory()) {
			std::string dir_name = entry.path().filename().string();
			// 关键修复：允许任意位数的数字
			if (dir_name.substr(0, 5) == "graph") {
				std::string num_str = dir_name.substr(5);
				// 检查剩余部分是否为纯数字
				if (std::all_of(num_str.begin(), num_str.end(), ::isdigit)) {
					try {
						int num = std::stoi(num_str);
						if (num > max_num) max_num = num;
					}
					catch (...) {}
				}
			}
		}
	}
	return max_num;
}

void GraphHandler::loadGraphFromFile(const std::string& filename) {
	std::ifstream file(filename);
	if (!file.is_open()) {
		throw std::runtime_error("无法打开文件: " + filename);
	}

	// 清空旧数据
	edges.clear();
	vertexPairs.clear();

	
	enum { None, Edges, VertexPairs } currentSection;
	currentSection = None;
	int edgeIdCounter = 0; // 动态生成边ID

	std::string line;
	while (std::getline(file, line)) {
		// 去除行首尾的空白字符
		size_t start = line.find_first_not_of(" \t");
		if (start == std::string::npos) continue; // 空行
		size_t end = line.find_last_not_of(" \t");
		line = line.substr(start, end - start + 1);

		if (line.empty()) continue;

		// 检查注释行切换数据段
		if (line[0] == '#') {
			if (line.find("Edges") != std::string::npos) {
				currentSection = Edges;
			}
			else if (line.find("Vertex Pairs") != std::string::npos) {
				currentSection = VertexPairs;
			}
			else {
				currentSection = None;
			}
			continue;
		}

		// 解析行数据
		std::istringstream iss(line);
		switch (currentSection) {
		case Edges: {
			Edge edge;
			try {
				if (!(iss >> edge.u >> edge.v >> edge.w_e >> edge.l_e)) {
					throw std::invalid_argument("无效的边数据行");
				}
				edges.push_back(edge);
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "警告: 忽略无效边数据行: " << line << " (" << e.what() << ")" << std::endl;
			}
			break;
		}
		case VertexPairs: {
			VertexPair pair;
			if (iss >> pair.s >> pair.t >> pair.a_i) {
				vertexPairs.push_back(pair); // 直接存储到成员变量
			}
			else {
				std::cerr << "警告: 忽略无效顶点对数据行: " << line << std::endl;
			}
			break;
		}
		default:
			break;
		}
	}
	// 输出读取的边信息
	std::cout << "读取的边信息:\n";
	for (const auto& edge : edges) {
		std::cout << "边 " << edge.u << " -> " << edge.v
			<< " (权重=" << edge.w_e << ", 长度=" << edge.l_e << ")\n";
	}

	// 输出读取的顶点对信息
	std::cout << "\n读取的顶点对信息:\n";
	for (const auto& pair : vertexPairs) {
		std::cout << "顶点对 " << pair.s << " -> " << pair.t
			<< " (活动值=" << pair.a_i << ")\n";
	}

	std::cout << "图数据加载完成。\n";
}
