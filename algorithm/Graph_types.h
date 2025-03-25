#pragma once
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/properties.hpp>
//�������
// �ߵĽṹ��
struct Edge {
	int u, v;
	float w_e, l_e; // w_e: Ȩ��, l_e: ����
	Edge() = default;
	Edge(int u, int v, float w_e, float l_e) : u(u), v(v), w_e(w_e), l_e(l_e) {};
};

// ����ԵĽṹ��
struct VertexPair {
	int s, t;
	float a_i; // ����Ե�Ȩ��
	VertexPair() = default;
	VertexPair(int s, int t, float a_i) : s(s), t(t), a_i(a_i) {};
};

//��װΪͼ����
// ���嶥������
struct VertexProperties {
	int id;        // �����ʶ��
	float x, y;    // �������� (x, y)
	// Ĭ�Ϲ��캯������ʼ�� id��x �� y ʹ��Ĭ��ֵ������ 0��
	VertexProperties() : id(0), x(0.0f), y(0.0f) {}
	// ��ʼ�� id��x �� y ʹ��Ĭ��ֵ������ 0.0��
	VertexProperties(int id) : id(id), x(0.0f), y(0.0f) {}
	// ���ι��캯������ʼ�� id��x �� y
	VertexProperties(int id, float x, float y) : id(id), x(x), y(y) {}

};
// ���������
struct EdgeProperties {
	int id;        // �߱�ʶ��
	float length;  // �ߵĳ���
	float width;   // �ߵĴ�ϸ
	float val;   // �ߵļ�ֵ
	// Ĭ�Ϲ��캯������ʼ�� id �� length��width ʹ��Ĭ��ֵ
	EdgeProperties() : id(0), length(0.0f), width(0.0f), val(0.0f) {}
	// ��ʼ��  id��length��widthʹ��Ĭ��ֵ
	EdgeProperties(int id, float length) : id(id), length(length), width(0.0f), val(1.0f) {}
	// ���ι��캯������ʼ�� id��length��width
	EdgeProperties(int id, float length, float val) : id(id), length(length), val(val), width(0.0f) {}

};
// ʹ�� adjacency_list ����ͼ������
typedef boost::adjacency_list<
	boost::vecS,              // ����洢�ṹ
	boost::vecS,              // �ߴ洢�ṹ
	boost::undirectedS,       // ����ͼ
	VertexProperties,         // ��������
	EdgeProperties           // ������
> Graph;

typedef std::unordered_map<int, boost::graph_traits<Graph>::vertex_descriptor> VertexIdMap;
typedef std::unordered_map<int, boost::graph_traits<Graph>::edge_descriptor> EdgeIdMap;

using VertexDescriptor = boost::graph_traits<Graph>::vertex_descriptor;  
using EdgeDescriptor = boost::graph_traits<Graph>::edge_descriptor;