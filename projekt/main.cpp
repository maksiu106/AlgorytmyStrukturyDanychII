#include <iostream>

#include "graph.hpp"
#include "smuggler.hpp"

//uwaga - w danych wejściowych metale indeksowane są od 1
//natomiast w grafie od 0

int main() {
	int metals; //mówi o liczbie wierzchołków
	int transform; //mówi o liczbie krawędzi
	int price;

	std::cin >> metals;

	Graph graph(metals);

	for (int i=0; i<metals; ++i) {
		std::cin >> price;
		graph.addVertice(i, price);
	}

	std::cin >> transform;
	for (int i=0; i<transform; ++i) {
		int start, end, price;
		std::cin >> start >> end >> price;
		graph.addEdge(start-1, end-1, price);
	}

	Smuggler smuggler(&graph);
	std::cout << smuggler.smuggle() << std::endl;
}
