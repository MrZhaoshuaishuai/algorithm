#pragma once
#include"Algorithm.h"
#include <random>
#include <algorithm>
class Recursion : public Algorithm {
private:
	const int RECURSE_NUM = 100;
public:
	Recursion() {}
	Recursion(GraphHandler graphHandler) : Algorithm(graphHandler) {}
	void recursionFunc() {
		//随机不放回的抽取，表示顶点对索引
		std::vector<int> temp_index;
		//用来存放边的使用信息
		int* edgesUsed = new int[graphHandler.edges.size()]();
		//用来记录路径的选择信息，以便在将来遍历时，判断是否需要跳过
		int* pathsUsed = new int[graphHandler.vertexPairs.size()];
		//初始化临时路径，默认取第一个
		for (int i = 0; i < graphHandler.vertexPairs.size(); i++) {
			for (auto i : graphHandler.vertexPairsPath[i][0]) {
				edgesUsed[i]++;
			}
			this->selected_paths.push_back(graphHandler.vertexPairsPath[i][0]);
			temp_index.push_back(i);
			pathsUsed[i] = 0;
		}
		//计算初始化路径的代价
		this->total_cost = computeCost(this->selected_paths);
		std::random_device rd;                  // 获取随机设备
		std::mt19937 g(rd());
		for (int i = 0; i < RECURSE_NUM; i++)
		{
			std::cout << "第" << i+1 << "轮迭代" << std::endl;
 			float costOld = this->total_cost;
			std::shuffle(temp_index.begin(), temp_index.end(), g);
			for (int j = 0; j < temp_index.size(); j++) {
				//取出第index个顶点对
				int index = temp_index[j];
				for (int k = 0; k < graphHandler.vertexPairsPath[index].size(); k++) {
					if (k == pathsUsed[index]) continue;
					//每次都是用computeCost
					/*this->selected_paths[index] = graphHandler.vertexPairsPath[index][k];
					float newCost = computeCost(this->selected_paths);
					if (newCost < this->total_cost) {
						this->total_cost = newCost;
						pathsUsed[index] = k;
					}
					else {
						this->selected_paths[index] = graphHandler.vertexPairsPath[index][pathsUsed[index]];
					}*/
					//不使用computeCost，计算差别，会有累计误差
					std::vector<int> oldPath = this->selected_paths[index];
					std::vector<int> newPath = graphHandler.vertexPairsPath[index][k];
					//接下来需要从线束和边两个角度判断代价是否降低
					//先求线束代价
					float w = graphHandler.vertexPairs[index].a_i;
					float oldHarnessSum = 0.0f;
					for (int p : oldPath) oldHarnessSum += graphHandler.graph[graphHandler.edgeMap[p]].length * w;
					float newHarnessSum = 0.0f;
					for (int p : newPath) newHarnessSum += graphHandler.graph[graphHandler.edgeMap[p]].length * w;
					//新线束比旧线束增加的代价
					float harnessCost = newHarnessSum - oldHarnessSum;
					//再求新边的代价
					float edgeCost = 0.0f;
					for (int p : oldPath) {
						edgesUsed[p]--;
						if(edgesUsed[p] == 0) edgeCost -= graphHandler.graph[graphHandler.edgeMap[p]].val;
					}
					for (int p : newPath) {
						if (edgesUsed[p] == 0) edgeCost += graphHandler.graph[graphHandler.edgeMap[p]].val;
						edgesUsed[p]++;
					}
					if (harnessCost + edgeCost < 0.0f) {
						this->total_cost = total_cost + harnessCost + edgeCost;
						pathsUsed[index] = k;
						this->selected_paths[index] = newPath;
					}
					else {
						//复原edgesUsed
						for (int p : oldPath) edgesUsed[p]++;
						for (int p : newPath) edgesUsed[p]--;
					}
				}
			}
			//浮点数比较
			if (costOld - this->total_cost < 1e-9) {
				std::cout << "找到最优解，停止迭代" << std::endl;
				return;
			}
		}
	}
};



////用来临时存放路径的，以便更新最优路径
//std::vector<std::vector<int>> temp_paths;
////随机不放回的抽取，表示顶点对索引
//std::vector<int> temp_index;
////初始化临时路径，默认取第一个
//for (int i = 0; i < graphHandler.vertexPairs.size(); i++) {
//	temp_paths.push_back(graphHandler.vertexPairsPath[i][0]);
//	temp_index.push_back(i);
//}
//std::random_device rd;                  // 获取随机设备
//std::mt19937 g(rd());
//for (int i = 0; i <= RECURSE_NUM; i++) {
//	//如果迭代到十的倍数，就判断是否小于已知最优值，小于就更新
//	float cost = computeCost(temp_paths);
//	if (cost < this->total_cost) {
//		this->total_cost = cost;
//		this->selected_paths = temp_paths;
//	}
//	//迭代完一次顶点对，就打乱，重新抽取
//	int index = i % graphHandler.vertexPairs.size();
//	if (index == 0) {
//		std::shuffle(temp_index.begin(), temp_index.end(), g);
//	}
//	int indexPair = temp_index[index];
//	int len = this->graphHandler.vertexPairsPath[indexPair].size();
//	//在该顶点对等概率中取出一个路径
//	std::uniform_int_distribution<> dis(0, len-1);
//	int random_index = dis(g);
//	temp_paths[indexPair] = this->graphHandler.vertexPairsPath[indexPair][random_index];
//}