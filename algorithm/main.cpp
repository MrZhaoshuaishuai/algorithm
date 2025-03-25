//#include<iostream>
//#include"GraphHandler.h"
//#include"Exhaustion.h"
//#include"Recursion.h"
//int main() {
//	GraphHandler graph(8, 10, 2);
//	graph.preHandle();
//	//��ٷ�
//	Exhaustion exhaustion(graph);
//	std::vector<std::vector<int>> vec;
//	std::cout << "��ٷ�ִ��" << std::endl;
//	auto start = std::chrono::high_resolution_clock::now();
//	exhaustion.exhaustionFunc(0, vec);
//	auto end = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double, std::milli> duration_ms = end - start;
//	exhaustion.printRes();
//	std::cout << "��ʱ��" << duration_ms.count() << "����" << std::endl;
//	exhaustion.visualizeGraphWithPaths(exhaustion.selected_paths);
//	
//	std::cout << "-------------------------------------------" << std::endl;
//
//	//������
//	Recursion recursion(graph);
//	std::cout << "������ִ��" << std::endl;
//	start = std::chrono::high_resolution_clock::now();
//	recursion.recursionFunc();
//	end = std::chrono::high_resolution_clock::now();
//	duration_ms = end - start;
//	recursion.printRes();
//	std::cout << "��ʱ��" << duration_ms.count() << "����" << std::endl;
//	recursion.visualizeGraphWithPaths(recursion.selected_paths);
//
//	return 0;
//}


#include <iostream>
#include <fstream>
#include <sstream>  // �����������ַ���������
#include <chrono>
#include "GraphHandler.h"
#include "Exhaustion.h"
#include "Recursion.h"

int main() {
    // ��ʼ��ͼ
    GraphHandler graph(8, 10, 4);
    double pre_time = graph.preHandle();

   

    // ��ٷ�����
    Exhaustion exhaustion(graph);
    {
        std::cout << "��ٷ�ִ��" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::vector<int>> vec;
        exhaustion.exhaustionFunc(0, vec);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        std::cout << "��ʱ��" << duration_ms.count() << "����" << std::endl;

        // ����̨���ԭ�н��
        exhaustion.printRes();
        //ֻ�е�flag=2ʱ��ȡ�ļ��е�ͼƬ���ż�¼�����
        if(graph.flag == 2)
        exhaustion.toExcel(graph, pre_time, duration_ms.count(),"path_exhaustion.csv");
    }

    // �ݹ鷨����
    Recursion recursion(graph);
    {
        std::cout << "������ִ��" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        recursion.recursionFunc();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        std::cout << "��ʱ��" << duration_ms.count() << "����" << std::endl;

        // ����̨���ԭ�н��
        recursion.printRes();

        if (graph.flag == 2)
        recursion.toExcel(graph, pre_time, duration_ms.count(), "path_recursion.csv");
    }
    return 0;
}