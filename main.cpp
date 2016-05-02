/*
 * File: main.cpp
 * Author: Brandon Hammel
 * Class: CS 130B, Spring 2016
 * Assignment: Programming Assignment
 */

#include <cstdlib>
#include <iostream>

using namespace std;

enum Methods {
	KILI = 1,
	PILI = 2,
	SILI = 3,
	FILI = 4,
	YILI = 5
};

int main(int argc, char **argv) {
	int method, numVertices, numEdges, k, output;
	int vertex1, vertex2;
	int weight;
	int *weights;

	cin >> method >> numVertices >> numEdges >> k >> output;

	if (method < 1 || method > 5) {
		cerr << "Error: Invalid method: " << method << endl;
		exit(1);
	} else if (output != 1 && output != 2) {
		cerr << "Error: Invalid output type: " << output << endl;
		exit(2);
	}

	for (int i = 0; i < numEdges; i++) {
		cin >> vertex1 >> vertex2;

		weights = new int[k];
		for (int j = 0; j < k; j++) {
			cin >> weight;
			weights[j] = weight;
		}

		delete[] weights;
	}

	return 0;
}
