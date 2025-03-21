#include<iostream>
#include"GraphHandler.h"
#include"Exhaustion.h"
#include"Recursion.h"
int main() {
	GraphHandler graph;
	graph.preHandle();
	//穷举法
	//Exhaustion exhaustion(graph);
	//std::vector<std::vector<int>> vec;
	//exhaustion.exhaustionFunc(0, vec);
	//exhaustion.printRes();


	//迭代法
	Recursion recursion(graph);
	recursion.recursionFunc();
	recursion.printRes();
	recursion.visualizeGraphWithPaths(recursion.selected_paths);

	return 0;
}