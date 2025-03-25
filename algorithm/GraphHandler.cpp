#include "GraphHandler.h"
#include<set>

#pragma once

void GraphHandler::generate(int n, int m, int k)
{
	edges.clear();
	vertexPairs.clear();

	// ������Ч����
	if (n <= 0) return;

	// --- ����߽���� ---
	if (n == 1) m = 0;          // ���������޷��γɱ�
	else m = std::max(m, n - 1); // ȷ������ �� n-1

	// --- ����������ͨͼ�ı��б� ---
	UnionFind uf(n);
	std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> vertexDist(0, n - 1);
	std::unordered_set<std::pair<int, int>, PairHash> edgeSet;

	// 1. ��������������֤��ͨ�ԣ�
	int edgesAdded = 0;
	while (edgesAdded < n - 1) {
		int u = vertexDist(gen), v = vertexDist(gen);
		if (u == v) continue;

		// ͳһ�洢Ϊ u <= v �����ظ�
		if (u > v) std::swap(u, v);
		if (uf.find(u) != uf.find(v)) {
			edges.emplace_back(u, v, (randomFloat() + 0.5f)*10.0f, (randomFloat()+0.5f)*10.0f);
			edgeSet.insert({ u, v });
			uf.unite(u, v);
			edgesAdded++;
		}
	}

	// 2. ������ʣ��ߣ�ȷ�����ظ���
	int remaining = m - (n - 1);
	int maxPossibleEdges = n * (n - 1) / 2; // ����ͼ������
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

	// --- ���ɶ�����б�s��t�Ҳ��ظ���---
	if (n < 2 || k <= 0) return;

	// �������п��ܵĶ���Բ�����
	std::vector<std::pair<int, int>> allPairs;
	for (int s = 0; s < n; ++s) {
		for (int t = 0; t < n; ++t) {
			if (s != t) allPairs.emplace_back(s, t);
		}
	}
	std::shuffle(allPairs.begin(), allPairs.end(), gen);

	// ȡǰk�����ظ��Ķ����
	k = std::min(k, static_cast<int>(allPairs.size()));
	for (int i = 0; i < k; ++i) {
		auto[s, t] = allPairs[i];
		vertexPairs.emplace_back(s, t, randomFloat()+0.5f);
	}
}

void GraphHandler::addToGraph()
{
	//��Ӷ���
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
	//��ӱ�
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
	std::cout << "Ԥ�����ʱ��" << duration_ms.count() << "����" << std::endl;
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
		throw std::invalid_argument("���Ѿ�����");
	}
	auto vertex = boost::add_vertex(v, graph);
	vertexMap[v.id] = vertex;
}

void GraphHandler::addEdge(int id1, int id2, EdgeProperties e)
{
	if (vertexMap.find(id1) == vertexMap.end() || vertexMap.find(id2) == vertexMap.end()) {
		throw std::invalid_argument("�����ڸõ�");
	}
	if (edgeMap.find(e.id) != edgeMap.end()) {
		throw std::invalid_argument("���Ѵ���");
	}
	auto v1 = vertexMap[id1];
	auto v2 = vertexMap[id2];
	auto edge = boost::add_edge(v1, v2, e, graph).first;
	edgeMap[e.id] = edge;  // ʹ��e.id��Ϊ�����洢��
}
// �������������ݵ��ļ�
void GraphHandler::saveToFile() {
	const std::string base_dir = "data";
	int next_num = findMaxGraphNumber(base_dir) + 1;

	// �ؼ��޸�����̬���㲹��λ�������ٲ���λ��
	int num_digits = std::max(2, (int)std::to_string(next_num).length());
	// ����Ŀ¼�����ļ���
	std::ostringstream dir_oss, file_oss;
	dir_oss << base_dir << "/graph"
		<< std::setw(num_digits) << std::setfill('0') << next_num;
	file_oss << "graph_data"
		<< std::setw(num_digits) << std::setfill('0') << next_num
		<< ".txt";

	// ����Ŀ¼
	fs::path dir_path(dir_oss.str());
	fs::create_directories(dir_path);

	// д���ļ�
	fs::path file_path = dir_path / file_oss.str();
	std::ofstream outfile(file_path);
	if (!outfile) {
		std::cerr << "Error writing to " << file_path << "\n";
		return;
	}

	// ����д��
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

	// �������������Ϣ������̨
	std::cout << "����Ϣ:\n";
	for (const auto& edge : edges) {
		std::cout << "Edge " << edge.u << "-" << edge.v
			<< " (w=" << edge.w_e << ", l=" << edge.l_e << ")\n";
	}

	std::cout << "�����ѱ�����: " << file_path << "\n";
}



int GraphHandler::findMaxGraphNumber(const std::string& base_dir) {
	int max_num = 0;

	if (!fs::exists(base_dir)) return 0;

	for (const auto& entry : fs::directory_iterator(base_dir)) {
		if (entry.is_directory()) {
			std::string dir_name = entry.path().filename().string();
			// �ؼ��޸�����������λ��������
			if (dir_name.substr(0, 5) == "graph") {
				std::string num_str = dir_name.substr(5);
				// ���ʣ�ಿ���Ƿ�Ϊ������
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
		throw std::runtime_error("�޷����ļ�: " + filename);
	}

	// ��վ�����
	edges.clear();
	vertexPairs.clear();

	
	enum { None, Edges, VertexPairs } currentSection;
	currentSection = None;
	int edgeIdCounter = 0; // ��̬���ɱ�ID

	std::string line;
	while (std::getline(file, line)) {
		// ȥ������β�Ŀհ��ַ�
		size_t start = line.find_first_not_of(" \t");
		if (start == std::string::npos) continue; // ����
		size_t end = line.find_last_not_of(" \t");
		line = line.substr(start, end - start + 1);

		if (line.empty()) continue;

		// ���ע�����л����ݶ�
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

		// ����������
		std::istringstream iss(line);
		switch (currentSection) {
		case Edges: {
			Edge edge;
			try {
				if (!(iss >> edge.u >> edge.v >> edge.w_e >> edge.l_e)) {
					throw std::invalid_argument("��Ч�ı�������");
				}
				edges.push_back(edge);
			}
			catch (const std::invalid_argument& e) {
				std::cerr << "����: ������Ч��������: " << line << " (" << e.what() << ")" << std::endl;
			}
			break;
		}
		case VertexPairs: {
			VertexPair pair;
			if (iss >> pair.s >> pair.t >> pair.a_i) {
				vertexPairs.push_back(pair); // ֱ�Ӵ洢����Ա����
			}
			else {
				std::cerr << "����: ������Ч�����������: " << line << std::endl;
			}
			break;
		}
		default:
			break;
		}
	}
	// �����ȡ�ı���Ϣ
	std::cout << "��ȡ�ı���Ϣ:\n";
	for (const auto& edge : edges) {
		std::cout << "�� " << edge.u << " -> " << edge.v
			<< " (Ȩ��=" << edge.w_e << ", ����=" << edge.l_e << ")\n";
	}

	// �����ȡ�Ķ������Ϣ
	std::cout << "\n��ȡ�Ķ������Ϣ:\n";
	for (const auto& pair : vertexPairs) {
		std::cout << "����� " << pair.s << " -> " << pair.t
			<< " (�ֵ=" << pair.a_i << ")\n";
	}

	std::cout << "ͼ���ݼ�����ɡ�\n";
}
