/*
 * File: KILI.hpp
 * Author: Brandon Hammel
 * Class: CS 130B, Spring 2016
 * Assignment: Programming Assignment
 */

#ifndef KILI_H
#define KILI_H

#include "Pair.hpp"

using namespace std;

#define edge Pair<int, int>
#define adjacency Pair<edge, int*>

class KILI {
private:
	int numNodes;
	int numEdges;
	int k;
	adjacency *graph;
	int *weightVector;
	adjacency *accepted;
	int ofv;
	int currentIndex;

	void mergeSort(adjacency *a, int n);
	void mergePass(adjacency *x, adjacency *y, int n, int segmentSize);
	void merge(adjacency *c, adjacency *d, int startOfFirst, int endOfFirst, int endOfSecond);
	int getOfv(adjacency a);
	bool lexicographicBefore(adjacency lhs, adjacency rhs);
public:
	KILI(int numNodes, int numEdges, int k);
	~KILI();
	void addEdge(int node1, int node2, int *weights);
	void sortEdges();
	bool findMST();
	void print(int type);
};

#endif
