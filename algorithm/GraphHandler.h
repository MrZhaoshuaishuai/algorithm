#pragma once
#include <vector>
#include <iostream>
#include <fstream>       // 新增：文件操作
#include <iomanip>       // 新增：控制输出格式
#include "Graph_types.h"
#include <boost/graph/graph_traits.hpp>
#include "PathFinder.h"
#include <unordered_set>
#include <random>
#include <algorithm>
#include <utility>
#include <filesystem>  // 新增：文件系统操作
namespace fs = std::filesystem;  // 新增：文件系统命名空间

// 辅助哈希函数用于 pair<int, int>
struct PairHash {
    size_t operator()(const std::pair<int, int>& p) const {
        return static_cast<size_t>(p.first) * 1000000 + p.second;
    }
};

class UnionFind {
private:
    std::vector<int> parent;
public:
    UnionFind(int size) {
        parent.resize(size);
        for (int i = 0; i < size; ++i) parent[i] = i;
    }

    int find(int x) {
        if (parent[x] != x) parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int x, int y) {
        int fx = find(x), fy = find(y);
        if (fx != fy) parent[fy] = fx;
    }
};

class GraphHandler {
public:
    std::vector<VertexPair> vertexPairs;
    std::vector<Edge> edges;
    std::vector<std::vector<std::vector<int>>> vertexPairsPath;
    Graph graph;
    VertexIdMap vertexMap;
    EdgeIdMap edgeMap;
    int flag = 0;

    GraphHandler() {}

    // 构造函数：生成数据并保存到文件
    GraphHandler(int vertexNum, int edgeNum, int pairNum) {  // 新增文件名参数
        
        std::cout << "***自动生成图请按 1 ***" << std::endl << "***读取图文件请按 2 ***" << std::endl;
        std::cin >> flag;
        if (flag == 1) {
            generate(vertexNum, edgeNum, pairNum);
            addToGraph();
            saveToFile();  // 生成后自动保存
        }
        else if(flag == 2){
            loadGraphFromFile("data/graph01/graph_data01.txt");
            addToGraph();
        }
        
    }

    // 新增：保存数据到文件
    void saveToFile();

    void addToGraph();
    double preHandle();
    void generate(int n, int m, int k);//顶点、边和顶点对

    // 新增：从文件加载图数据到成员变量
    void loadGraphFromFile(const std::string& filename);


private:
    // 随机数生成（原有实现不变）
    float randomFloat() {
        static std::mt19937 gen(std::random_device{}());
        static std::uniform_real_distribution<float> dis(
            std::nextafter(0.0f, 1.0f),
            std::nextafter(1.0f, 0.0f)
        );
        return dis(gen);
    }

    void addVertex(VertexProperties v);
    void addEdge(int id1, int id2, EdgeProperties e);



    // 查找现有最大编号的目录
    int findMaxGraphNumber(const std::string& base_dir);
};