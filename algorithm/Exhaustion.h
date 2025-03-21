#pragma once
#include"Algorithm.h"
class Exhaustion : public Algorithm {
public:
	Exhaustion() {}
	Exhaustion(GraphHandler graphHandler) : Algorithm(graphHandler) {}

	void exhaustionFunc(int idx, std::vector<std::vector<int>> current_selection)
	{
		// 递归结束条件：如果遍历完了所有的二维数组
		if (idx == graphHandler.vertexPairsPath.size()) {
			float cost = computeCost(current_selection);
			if (cost < total_cost) {
				total_cost = cost;
				selected_paths = current_selection;
			}
			return;
		}

		// 遍历当前二维数组中的所有路径，递归选择每一条路径
		for (const auto& path : graphHandler.vertexPairsPath[idx]) {
			current_selection.push_back(path);
			exhaustionFunc(idx + 1, current_selection);
			current_selection.pop_back();  // 回溯
		}
	}
};
