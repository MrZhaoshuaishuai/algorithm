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
		//������Żصĳ�ȡ����ʾ���������
		std::vector<int> temp_index;
		//������űߵ�ʹ����Ϣ
		int* edgesUsed = new int[graphHandler.edges.size()]();
		//������¼·����ѡ����Ϣ���Ա��ڽ�������ʱ���ж��Ƿ���Ҫ����
		int* pathsUsed = new int[graphHandler.vertexPairs.size()];
		//��ʼ����ʱ·����Ĭ��ȡ��һ��
		for (int i = 0; i < graphHandler.vertexPairs.size(); i++) {
			for (auto i : graphHandler.vertexPairsPath[i][0]) {
				edgesUsed[i]++;
			}
			this->selected_paths.push_back(graphHandler.vertexPairsPath[i][0]);
			temp_index.push_back(i);
			pathsUsed[i] = 0;
		}
		//�����ʼ��·���Ĵ���
		this->total_cost = computeCost(this->selected_paths);
		std::random_device rd;                  // ��ȡ����豸
		std::mt19937 g(rd());
		for (int i = 0; i < RECURSE_NUM; i++)
		{
			std::cout << "��" << i+1 << "�ֵ���" << std::endl;
 			float costOld = this->total_cost;
			std::shuffle(temp_index.begin(), temp_index.end(), g);
			for (int j = 0; j < temp_index.size(); j++) {
				//ȡ����index�������
				int index = temp_index[j];
				for (int k = 0; k < graphHandler.vertexPairsPath[index].size(); k++) {
					if (k == pathsUsed[index]) continue;
					//ÿ�ζ�����computeCost
					/*this->selected_paths[index] = graphHandler.vertexPairsPath[index][k];
					float newCost = computeCost(this->selected_paths);
					if (newCost < this->total_cost) {
						this->total_cost = newCost;
						pathsUsed[index] = k;
					}
					else {
						this->selected_paths[index] = graphHandler.vertexPairsPath[index][pathsUsed[index]];
					}*/
					//��ʹ��computeCost�������𣬻����ۼ����
					std::vector<int> oldPath = this->selected_paths[index];
					std::vector<int> newPath = graphHandler.vertexPairsPath[index][k];
					//��������Ҫ�������ͱ������Ƕ��жϴ����Ƿ񽵵�
					//������������
					float w = graphHandler.vertexPairs[index].a_i;
					float oldHarnessSum = 0.0f;
					for (int p : oldPath) oldHarnessSum += graphHandler.graph[graphHandler.edgeMap[p]].length * w;
					float newHarnessSum = 0.0f;
					for (int p : newPath) newHarnessSum += graphHandler.graph[graphHandler.edgeMap[p]].length * w;
					//�������Ⱦ��������ӵĴ���
					float harnessCost = newHarnessSum - oldHarnessSum;
					//�����±ߵĴ���
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
						//��ԭedgesUsed
						for (int p : oldPath) edgesUsed[p]++;
						for (int p : newPath) edgesUsed[p]--;
					}
				}
			}
			//�������Ƚ�
			if (costOld - this->total_cost < 1e-9) {
				std::cout << "�ҵ����Ž⣬ֹͣ����" << std::endl;
				return;
			}
		}
	}
};



////������ʱ���·���ģ��Ա��������·��
//std::vector<std::vector<int>> temp_paths;
////������Żصĳ�ȡ����ʾ���������
//std::vector<int> temp_index;
////��ʼ����ʱ·����Ĭ��ȡ��һ��
//for (int i = 0; i < graphHandler.vertexPairs.size(); i++) {
//	temp_paths.push_back(graphHandler.vertexPairsPath[i][0]);
//	temp_index.push_back(i);
//}
//std::random_device rd;                  // ��ȡ����豸
//std::mt19937 g(rd());
//for (int i = 0; i <= RECURSE_NUM; i++) {
//	//���������ʮ�ı��������ж��Ƿ�С����֪����ֵ��С�ھ͸���
//	float cost = computeCost(temp_paths);
//	if (cost < this->total_cost) {
//		this->total_cost = cost;
//		this->selected_paths = temp_paths;
//	}
//	//������һ�ζ���ԣ��ʹ��ң����³�ȡ
//	int index = i % graphHandler.vertexPairs.size();
//	if (index == 0) {
//		std::shuffle(temp_index.begin(), temp_index.end(), g);
//	}
//	int indexPair = temp_index[index];
//	int len = this->graphHandler.vertexPairsPath[indexPair].size();
//	//�ڸö���Եȸ�����ȡ��һ��·��
//	std::uniform_int_distribution<> dis(0, len-1);
//	int random_index = dis(g);
//	temp_paths[indexPair] = this->graphHandler.vertexPairsPath[indexPair][random_index];
//}