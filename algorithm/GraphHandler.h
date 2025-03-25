#pragma once
#include <vector>
#include <iostream>
#include <fstream>       // �������ļ�����
#include <iomanip>       // ���������������ʽ
#include "Graph_types.h"
#include <boost/graph/graph_traits.hpp>
#include "PathFinder.h"
#include <unordered_set>
#include <random>
#include <algorithm>
#include <utility>
#include <filesystem>  // �������ļ�ϵͳ����
namespace fs = std::filesystem;  // �������ļ�ϵͳ�����ռ�

// ������ϣ�������� pair<int, int>
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

    // ���캯�����������ݲ����浽�ļ�
    GraphHandler(int vertexNum, int edgeNum, int pairNum) {  // �����ļ�������
        
        std::cout << "***�Զ�����ͼ�밴 1 ***" << std::endl << "***��ȡͼ�ļ��밴 2 ***" << std::endl;
        std::cin >> flag;
        if (flag == 1) {
            generate(vertexNum, edgeNum, pairNum);
            addToGraph();
            saveToFile();  // ���ɺ��Զ�����
        }
        else if(flag == 2){
            loadGraphFromFile("data/graph01/graph_data01.txt");
            addToGraph();
        }
        
    }

    // �������������ݵ��ļ�
    void saveToFile();

    void addToGraph();
    double preHandle();
    void generate(int n, int m, int k);//���㡢�ߺͶ����

    // ���������ļ�����ͼ���ݵ���Ա����
    void loadGraphFromFile(const std::string& filename);


private:
    // ��������ɣ�ԭ��ʵ�ֲ��䣩
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



    // ������������ŵ�Ŀ¼
    int findMaxGraphNumber(const std::string& base_dir);
};