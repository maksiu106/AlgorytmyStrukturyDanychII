#ifndef SMUGGLER_HPP_
#define SMUGGLER_HPP_

#include "graph.hpp"
#include "heap.hpp"

class Smuggler {
	Graph* graph;
	int n; //liczba metali
	int* duty; //tablica z cłem, jakie trzeba zapłacić za transport każdego metali
	int* from_gold; //tablica z cenami otrzymania każdego metalu ze złota
	int* to_gold; //tablica z cenami otrzymania złota z każdego metalu o danym id
	int result; //koszt najtańszej ścieżki szmuglowania

	void dijkstraFromGold() {
		for (int i=0; i<n; ++i) {
			from_gold[i] = 1000000000;
		}

		from_gold[0] = 0;
		PriorityQueue<int> pq(n);
		for (int i=0; i<n; ++i) {
			pq.insert(i, from_gold[i]);
		}

		while (!pq.empty()) {
			int v = pq.extractMin();
			for (std::pair<int, int> p : graph->outConnections(v)) {
				if (from_gold[p.first] > from_gold[v] + p.second) {
					from_gold[p.first] = from_gold[v] + p.second;
					pq.change(p.first, from_gold[p.first]);
				}

			}
		}
	}

	void dijkstraToGold(int start) {
		int result[n];
		for (int i=0; i<n; ++i) {
			result[i] = 1000000000;
		}

		result[start] = 0;
		PriorityQueue<int> pq(n);
		for (int i=0; i<n; ++i) {
			pq.insert(i, result[i]);
		}

		while (!pq.empty()) {
			int v = pq.extractMin();
			for (std::pair<int, int> p : graph->outConnections(v)) {
				if (result[p.first] > result[v] + p.second) {
					result[p.first] = result[v] + p.second;
					pq.change(p.first, result[p.first]);
				}
				if (v == 0) {
					to_gold[start] = result[0];
					return;
				}
			}
		}
	}

	void calculateDuty() {
		for (int i=0; i<n; ++i) {
			duty[i] = graph->getPrice(i)/2;
		}
	}

public:
	Smuggler(Graph* g){
		graph = g;
		n = graph->size();
		duty = new int[n];
		from_gold = new int[n];
		to_gold = new int[n];

		calculateDuty();
		dijkstraFromGold();
		for (int i=0; i<n; ++i) {
			dijkstraToGold(i);
		}

		int fullCost[n];
		int min = 1000000000;
		for (int i=0; i<n; ++i) {
			fullCost[i] = duty[i] + from_gold[i] + to_gold[i];
			if (fullCost[i] < min) min = fullCost[i];
		}

		result = min;
	}

	~Smuggler() {
		delete[] duty;
		delete[] from_gold;
		delete[] to_gold;
	}

	int smuggle() {
		return result;
	}
};

#endif /* SMUGGLER_HPP_ */
