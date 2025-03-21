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
		//������ʱ���·���ģ��Ա��������·��
		std::vector<std::vector<int>> temp_paths;
		//������Żصĳ�ȡ����ʾ���������
		std::vector<int> temp_index;
		//��ʼ����ʱ·����Ĭ��ȡ��һ��
		for (int i = 0; i < graphHandler.vertexPairs.size(); i++) {
			temp_paths.push_back(graphHandler.vertexPairsPath[i][0]);
			temp_index.push_back(i);
		}
		std::random_device rd;                  // ��ȡ����豸
		std::mt19937 g(rd());
		for (int i = 0; i <= RECURSE_NUM; i++) {
			//���������ʮ�ı��������ж��Ƿ�С����֪����ֵ��С�ھ͸���
			if (i%SAVE_NUM == 0) {
				float cost = computeCost(temp_paths);
				if (cost < this->total_cost) {
					this->total_cost = cost;
					this->selected_paths = temp_paths;
				}
			}
			//������һ�ζ���ԣ��ʹ��ң����³�ȡ
			int index = i % graphHandler.vertexPairs.size();
			if (index == 0) {
				std::shuffle(temp_index.begin(), temp_index.end(), g);
			}
			int indexPair = temp_index[index];
			int len = this->graphHandler.vertexPairsPath[indexPair].size();
			//�ڸö���Եȸ�����ȡ��һ��·��
			std::uniform_int_distribution<> dis(0, len-1);
			int random_index = dis(g);
			temp_paths[indexPair] = this->graphHandler.vertexPairsPath[indexPair][random_index];
		}
	}
};