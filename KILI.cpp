/*
 * File: KILI.cpp
 * Author: Brandon Hammel
 * Class: CS 130B, Spring 2016
 * Assignment: Programming Assignment
 */

#include <cstdlib>
#include <iostream>
#include "KILI.hpp"

KILI::KILI(int numNodes, int numEdges, int k) {
	this->numNodes = numNodes;
	this->numEdges = numEdges;
	this->k = k;
	this->graph = new adjacency[numEdges]();
	this->weightVector = new int[k]();
	this->accepted = new adjacency[numNodes - 1]();
	this->ofv = 0;
	this->currentIndex = 0;
}

KILI::~KILI() {
	delete[] graph;
	delete[] weightVector;
	delete[] accepted;
}

void KILI::addEdge(int node1, int node2, int *weights) {
	if (this->currentIndex < 0 || this->currentIndex >= this->numEdges) {
		cerr << "Error: Cannot add edge at index " << this->currentIndex << " to graph" << endl;
		exit(1);
	}

	this->graph[this->currentIndex++] = adjacency(edge(node1, node2), weights);
}

void KILI::sortEdges() {
	this->mergeSort(this->graph, this->numEdges);
}

bool KILI::findMST() {
	// When adding to accepted, set its weight to 0
	return false;
}

void KILI::print(int type) {
	if (type != 1 && type != 2) {
		cerr << "Error: Invalid output type: " << type << endl;
		exit(2);
	}

	if (type == 1) {
		int first, second;

		this->mergeSort(this->accepted, this->numNodes - 1);

		for (int i = 0; i < this->numNodes - 1; i++) {
			if (this->accepted[i].first.first <= this->accepted[i].first.second) {
				first = this->accepted[i].first.first;
				second = this->accepted[i].first.second;
			} else {
				first = this->accepted[i].first.second;
				second = this->accepted[i].first.first;
			}

			cout << first << " " << second << endl;
		}
	}

	for (int i = 0; i < this->k; i++) {
		cout << this->weightVector[i] << " ";
	}
	cout << endl;

	cout << "KILI " << this->ofv << endl;
}

void KILI::mergeSort(adjacency *a, int n) {
	// Sort a[0:n - 1] using the merge sort method.
	adjacency *b = new adjacency[n];
	int segmentSize = 1;
	while (segmentSize < n) {
		mergePass(a, b, n, segmentSize);	// merge from a to b
		segmentSize += segmentSize;
		mergePass(b, a, n, segmentSize);	// merge from b to a
		segmentSize += segmentSize;
	}
}

void KILI::mergePass(adjacency *x, adjacency *y, int n, int segmentSize) {
	// Merge adjacent segments from x to y.
	int i = 0;	// start of the next segment
	while (i <= n - 2 * segmentSize) {
		// merge two adjacent segments from x to y
		merge(x, y, i, i + segmentSize - 1, i + 2 * segmentSize - 1);
		i = i + 2 * segmentSize;
	}

	// fewer than 2 full segments remain
	if (i + segmentSize < n) {
		// 2 segments remain
		merge(x, y, i, i + segmentSize - 1, n - 1);
	} else {
		// 1 segment remains, copy to y
		for (int j = i; j < n; j++) {
			y[j] = x[j];
		}
	}
}

void KILI::merge(adjacency *c, adjacency *d, int startOfFirst, int endOfFirst, int endOfSecond) {
	// Merge two adjacent segments from c to d.
	int first = startOfFirst,	// cursor for first segment
	second = endOfFirst + 1,	// cursor for second
	result = startOfFirst;		// cursor for result

	// merge until one segment is done
	while ((first <= endOfFirst) && (second <= endOfSecond)) {
		if (getOfv(c[first]) < getOfv(c[second])) {
			d[result++] = c[first++];
		} else if (getOfv(c[first]) == getOfv(c[second])) {
			if (lexicographicBefore(c[first], c[second])) {
				d[result++] = c[first++];
			} else {
				d[result++] = c[second++];
			}
		} else {
			d[result++] = c[second++];
		}
	}

	// take care of leftovers
	if (first > endOfFirst) {
		for (int i = second; i <= endOfSecond; i++) {
			d[result++] = c[i];
		}
	} else {
		for (int i = first; i <= endOfFirst; i++) {
			d[result++] = c[i];
		}
	}
}

int KILI::getOfv(adjacency a) {
	int ofv = 0;

	for (int i = 0; i < this->k; i++) {
		if (a.second[i] > ofv) {
			ofv = a.second[i];
		}
	}

	return ofv;
}

bool KILI::lexicographicBefore(adjacency lhs, adjacency rhs) {
	int min1, min2;

	if (lhs.first.first <= lhs.first.second) {
		min1 = lhs.first.first;
	} else {
		min1 = lhs.first.second;
	}

	if (rhs.first.first <= rhs.first.second) {
		min2 = rhs.first.first;
	} else {
		min2 = rhs.first.second;
	}

	if (min1 < min2) {
		return true;
	} else if (min1 == min2) {
		int max1, max2;

		if (lhs.first.first >= lhs.first.second) {
			max1 = lhs.first.first;
		} else {
			max1 = lhs.first.second;
		}

		if (rhs.first.first >= rhs.first.second) {
			max2 = rhs.first.first;
		} else {
			max2 = rhs.first.second;
		}

		if (max1 < max2) {
			return true;
		}
	}

	return false;
}
