//#include<iostream>
//#include"GraphHandler.h"
//#include"Exhaustion.h"
//#include"Recursion.h"
//int main() {
//	GraphHandler graph(8, 10, 2);
//	graph.preHandle();
//	//穷举法
//	Exhaustion exhaustion(graph);
//	std::vector<std::vector<int>> vec;
//	std::cout << "穷举法执行" << std::endl;
//	auto start = std::chrono::high_resolution_clock::now();
//	exhaustion.exhaustionFunc(0, vec);
//	auto end = std::chrono::high_resolution_clock::now();
//	std::chrono::duration<double, std::milli> duration_ms = end - start;
//	exhaustion.printRes();
//	std::cout << "耗时：" << duration_ms.count() << "毫秒" << std::endl;
//	exhaustion.visualizeGraphWithPaths(exhaustion.selected_paths);
//	
//	std::cout << "-------------------------------------------" << std::endl;
//
//	//迭代法
//	Recursion recursion(graph);
//	std::cout << "迭代法执行" << std::endl;
//	start = std::chrono::high_resolution_clock::now();
//	recursion.recursionFunc();
//	end = std::chrono::high_resolution_clock::now();
//	duration_ms = end - start;
//	recursion.printRes();
//	std::cout << "耗时：" << duration_ms.count() << "毫秒" << std::endl;
//	recursion.visualizeGraphWithPaths(recursion.selected_paths);
//
//	return 0;
//}


#include <iostream>
#include <fstream>
#include <sstream>  // 新增：用于字符串流操作
#include <chrono>
#include "GraphHandler.h"
#include "Exhaustion.h"
#include "Recursion.h"

int main() {
    // 初始化图
    GraphHandler graph(8, 10, 4);
    double pre_time = graph.preHandle();

   

    // 穷举法部分
    Exhaustion exhaustion(graph);
    {
        std::cout << "穷举法执行" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<std::vector<int>> vec;
        exhaustion.exhaustionFunc(0, vec);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        std::cout << "耗时：" << duration_ms.count() << "毫秒" << std::endl;

        // 控制台输出原有结果
        exhaustion.printRes();
        //只有当flag=2时读取文件中的图片，才记录结果。
        if(graph.flag == 2)
        exhaustion.toExcel(graph, pre_time, duration_ms.count(),"path_exhaustion.csv");
    }

    // 递归法部分
    Recursion recursion(graph);
    {
        std::cout << "迭代法执行" << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        recursion.recursionFunc();
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> duration_ms = end - start;
        std::cout << "耗时：" << duration_ms.count() << "毫秒" << std::endl;

        // 控制台输出原有结果
        recursion.printRes();

        if (graph.flag == 2)
        recursion.toExcel(graph, pre_time, duration_ms.count(), "path_recursion.csv");
    }
    return 0;
}