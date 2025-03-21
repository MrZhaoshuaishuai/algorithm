#pragma once
#include"Algorithm.h"
#include <random>
#include <algorithm>
class Recursion : public Algorithm {
private:
	const int RECURSE_NUM = 1000;
	const int SAVE_NUM = 10;
public:
	Recursion() {}
	Recursion(GraphHandler graphHandler) : Algorithm(graphHandler) {}
	void recursionFunc() {
		//用来临时存放路径的，以便更新最优路径
		std::vector<std::vector<int>> temp_paths;
		//随机不放回的抽取，表示顶点对索引
		std::vector<int> temp_index;
		//初始化临时路径，默认取第一个
		for (int i = 0; i < graphHandler.vertexPairs.size(); i++) {
			temp_paths.push_back(graphHandler.vertexPairsPath[i][0]);
			temp_index.push_back(i);
		}
		std::random_device rd;                  // 获取随机设备
		std::mt19937 g(rd());
		for (int i = 0; i <= RECURSE_NUM; i++) {
			//如果迭代到十的倍数，就判断是否小于已知最优值，小于就更新
			if (i%SAVE_NUM == 0) {
				float cost = computeCost(temp_paths);
				if (cost < this->total_cost) {
					this->total_cost = cost;
					this->selected_paths = temp_paths;
				}
			}
			//迭代完一次顶点对，就打乱，重新抽取
			int index = i % graphHandler.vertexPairs.size();
			if (index == 0) {
				std::shuffle(temp_index.begin(), temp_index.end(), g);
			}
			int indexPair = temp_index[index];
			int len = this->graphHandler.vertexPairsPath[indexPair].size();
			//在该顶点对等概率中取出一个路径
			std::uniform_int_distribution<> dis(0, len-1);
			int random_index = dis(g);
			temp_paths[indexPair] = this->graphHandler.vertexPairsPath[indexPair][random_index];
		}
	}
};