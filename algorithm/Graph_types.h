#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
//输入参数
// 边的结构体
struct Edge {
	int u, v;
	float w_e, l_e; // w_e: 权重, l_e: 长度
	Edge() = default;
	Edge(int u, int v, float w_e, float l_e) : u(u), v(v), w_e(w_e), l_e(l_e) {};
};

// 顶点对的结构体
struct VertexPair {
	int s, t;
	float a_i; // 顶点对的权重
	VertexPair() = default;
	VertexPair(int s, int t, float a_i) : s(s), t(t), a_i(a_i) {};
};

//封装为图参数
// 定义顶点属性
struct VertexProperties {
	int id;        // 顶点标识符
	float x, y;    // 顶点坐标 (x, y)
	// 默认构造函数，初始化 id，x 和 y 使用默认值（比如 0）
	VertexProperties() : id(0), x(0.0f), y(0.0f) {}
	// 初始化 id，x 和 y 使用默认值（比如 0.0）
	VertexProperties(int id) : id(id), x(0.0f), y(0.0f) {}
	// 带参构造函数，初始化 id、x 和 y
	VertexProperties(int id, float x, float y) : id(id), x(x), y(y) {}

};
// 定义边属性
struct EdgeProperties {
	int id;        // 边标识符
	float length;  // 边的长度
	float width;   // 边的粗细
	float val;   // 边的价值
	// 默认构造函数，初始化 id 和 length，width 使用默认值
	EdgeProperties() : id(0), length(0.0f), width(0.0f), val(0.0f) {}
	// 初始化  id和length，width使用默认值
	EdgeProperties(int id, float length) : id(id), length(length), width(0.0f), val(1.0f) {}
	// 带参构造函数，初始化 id、length和width
	EdgeProperties(int id, float length, float val) : id(id), length(length), val(val), width(0.0f) {}

};
// 使用 adjacency_list 创建图的类型
typedef boost::adjacency_list<
	boost::vecS,              // 顶点存储结构
	boost::vecS,              // 边存储结构
	boost::undirectedS,       // 无向图
	VertexProperties,         // 顶点属性
	EdgeProperties           // 边属性
> Graph;

typedef std::unordered_map<int, boost::graph_traits<Graph>::vertex_descriptor> VertexIdMap;
typedef std::unordered_map<int, boost::graph_traits<Graph>::edge_descriptor> EdgeIdMap;

using VertexDescriptor = boost::graph_traits<Graph>::vertex_descriptor;  
using EdgeDescriptor = boost::graph_traits<Graph>::edge_descriptor;