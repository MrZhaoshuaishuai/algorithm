#pragma once
#include"Algorithm.h"
class Exhaustion : public Algorithm {
public:
	Exhaustion() {}
	Exhaustion(GraphHandler graphHandler) : Algorithm(graphHandler) {}

	void exhaustionFunc(int idx, std::vector<std::vector<int>> current_selection)
	{
		// �ݹ������������������������еĶ�ά����
		if (idx == graphHandler.vertexPairsPath.size()) {
			float cost = computeCost(current_selection);
			if (cost < total_cost) {
				total_cost = cost;
				selected_paths = current_selection;
			}
			return;
		}

		// ������ǰ��ά�����е�����·�����ݹ�ѡ��ÿһ��·��
		for (const auto& path : graphHandler.vertexPairsPath[idx]) {
			current_selection.push_back(path);
			exhaustionFunc(idx + 1, current_selection);
			current_selection.pop_back();  // ����
		}
	}
};
